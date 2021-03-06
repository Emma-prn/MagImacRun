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

using namespace glimac;

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
                case SDL_KEYUP:
                    switch (e.key.keysym.sym) {
                        case SDLK_z:
                            mapAndJ.second.land();
                            break;
                        case SDLK_s:
                            mapAndJ.second.standUp();
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_z:
                            mapAndJ.second.jump();
                            break;
                        case SDLK_s:
                            mapAndJ.second.slide();
                            break;
                        case SDLK_q:
                            mapAndJ.second.turnLeft();
                            break;
                        case SDLK_d:
                            mapAndJ.second.turnRight();
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
            //mapAndJ.first.crystals[i]->crystalDraw(camP->getViewMatrix(mapAndJ.second), Projection, windowManager);
        }
        mapAndJ.second.move();
        if(!mapAndJ.first.isAlive(mapAndJ.second)){
            if(!mapAndJ.second.isJumping()){
                mapAndJ.second.fall();
            }
        }
        glDepthFunc(GL_LESS);
        // Update the display
        windowManager.swapBuffers();
    }
    return EXIT_SUCCESS;
}