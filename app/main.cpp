#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <graphics/Cam.hpp>
#include <graphics/Cam2.hpp> 
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <utility>
#include <glimac/Skybox.hpp>
#include <graphics/readFile.hpp>
#include <graphics/crystal.hpp> 
#include <glimac/Texture.hpp>
#include <graphics/Objet.hpp>
#include <graphics/Rectangle.hpp>
#include <graphics/Dessin.hpp>

using namespace glimac;

struct Vertex2DColor{

    public:
        glm::vec2 position;
        glm::vec3 color;

        Vertex2DColor(glm::vec2 position, glm::vec3 color);
        Vertex2DColor();
};

Vertex2DColor::Vertex2DColor(glm::vec2 position, glm::vec3 color){

    this-> position = position;

    this->color = color;
};

Vertex2DColor::Vertex2DColor(){
 
    this->position = glm::vec2(0.0f,0.0f);

    this->color = glm::vec3(0.0f,0.0f,0.0f);
}

float width = 800;
float height = 600;
bool isBlocked = false;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(width, height, "MagImacRun");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    Skybox sky(applicationPath);
    std::pair<Map,geo::Joueur> mapAndJ = readMap("../assets/map/map.txt", applicationPath);
    CamFPers cam(mapAndJ.second);
    CamTPers camT;
    CamA* camP = &camT;
    //Crystal cristal(1, 32, 16,applicationPath); 
    Texture menuTexture(applicationPath, "forest.jpg");
    Rectangle menu(10, 5);

    Dessin menuProgram(applicationPath, "projet.vs.glsl", "projet.fs.glsl", menu);

    bool pause = false
    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            switch (e.type)
            {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_z:
                            break;
                        case SDLK_s:
                            break;
                        case SDLK_q:
                            break;
                        case SDLK_d:
                            break;
                        case SDLK_l:
                            isBlocked = !isBlocked;
                            break;
                        case SDLK_c:
                            {
                                if (camP == &camT)
                                {
                                    camP = &cam;
                                }
                                else {
                                    camP = &camT;
                                }
                            }
                            break;
                        case SDLK_ESCAPE:
                            if(pause == false){
                                pause = true;
                            }
                            else{
                                pause = false;
                            }

                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (SDL_GetMouseState(nullptr,nullptr) & SDL_BUTTON_LMASK && !isBlocked)
                    {
                        float camX = float(e.motion.xrel);
                        float camY = float(e.motion.yrel);
                        camP->rotateUp(camY);
                        camP->rotateLeft(camX);
                    }
                    else if ((SDL_GetMouseState(nullptr,nullptr) & SDL_BUTTON_MMASK && !isBlocked) && camP == &camT)
                    {
                        if (e.motion.yrel > 0)
                        {
                            camT.moveFront(0.1);
                        }
                        else if (e.motion.yrel < 0){
                            camT.moveFront(-0.1);
                        }
                    }
                   break;
                default:
                    break;
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glDepthFunc(GL_LEQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 Projection = glm::perspective(glm::radians(70.f),float(width/height),0.1f,100.f);
        glm::mat4 View = glm::mat4(glm::mat3(camP->getViewMatrix(mapAndJ.second)));
        View = glm::scale(View, glm::vec3(0.2,0.2,0.2));

        sky.renderSkybox(View,Projection);
        glEnable(GL_DEPTH_TEST);
        for (float i = 0; i < mapAndJ.first.tiles.size(); i++)
        {
            mapAndJ.first.tiles[i]->draw(camP->getViewMatrix(mapAndJ.second), Projection);
        }
        //mapAndJ.second.move();
        //cristal.crystalDraw(View, Projection, windowManager);
        glDepthFunc(GL_LESS);
        // Update the display

        glm::mat4 menuMVMatrix;
        menuMVMatrix = glm::translate(globalMVMatrix, glm::vec3(0, 1, 0));
        menuMVMatrix = glm::rotate(globalMVMatrix, 90.0f, glm::vec3(1, 0, 0));
        
        if (pause == true){
            menuProgram.draw(menuTexture, menuMVMatrix, projMatrix);
        }

        windowManager.swapBuffers();
    }
    return EXIT_SUCCESS;
}