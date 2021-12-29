#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/TrackballCamera.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glimac/Skybox.hpp>
#include <graphics/readFile.hpp>
#include <graphics/camera.hpp>
#include <graphics/tile.hpp>
#include <graphics/wall.hpp>

using namespace glimac;

struct SkyboxProgram {
    Program m_Program;

    GLint uPMatrix;
    GLint uVMatrix;
    GLint uSky;

    SkyboxProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/skybox.vs.glsl",
                              applicationPath.dirPath() + "shaders/skybox.fs.glsl")) {
        uPMatrix = glGetUniformLocation(m_Program.getGLId(), "projection");
        uVMatrix = glGetUniformLocation(m_Program.getGLId(), "view");
        uSky = glGetUniformLocation(m_Program.getGLId(), "skybox");
    }
};

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
    SkyboxProgram skyboxProgram(applicationPath);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    Skybox sky;
    Map parcours = readMap("../assets/map/map.txt", applicationPath);
    TrackballCamera cam(0.1, 2., 1.); 
    /*camera cam(70.f,0.1f,100.f);
    cam.set_screen_dimensions(width,height);*/

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
                        case SDLK_c:
                            isBlocked = !isBlocked;
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
                        cam.rotateUp(camY);
                        cam.rotateLeft(camX);
                        //cam.look_at(glm::vec3(camY,camX,cam.billboard_normal().z));
                    }
                    else if (SDL_GetMouseState(nullptr,nullptr) & SDL_BUTTON_MMASK && !isBlocked)
                    {
                        if (e.motion.yrel > 0)
                        {
                            cam.moveFront(0.1);
                            //cam.move_to(0.1);
                        }
                        else if (e.motion.yrel < 0){
                            cam.moveFront(-0.1);
                            //cam.move_to(-0.1);
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
        skyboxProgram.m_Program.use();
        glDepthFunc(GL_LEQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 Projection = glm::perspective(glm::radians(70.f),float(width/height),0.1f,100.f);
        glm::mat4 View = glm::mat4(glm::mat3(cam.getViewMatrix()));

        /*glm::mat4 Projection = cam.projection();
        glm::mat4 View = glm::mat4(glm::mat3(cam.view()));*/

        glUniformMatrix4fv(skyboxProgram.uVMatrix, 1, GL_FALSE, glm::value_ptr(View));
        glUniformMatrix4fv(skyboxProgram.uPMatrix, 1, GL_FALSE, glm::value_ptr(Projection));
        sky.renderSkybox();
        glEnable(GL_DEPTH_TEST);
        for (float i = 0; i < parcours.tiles.size(); i++)
        {
            parcours.tiles[i]->draw(cam.getViewMatrix(), Projection);
        }
        glDepthFunc(GL_LESS);

        // Update the display
        windowManager.swapBuffers();
    }
    return EXIT_SUCCESS;
}