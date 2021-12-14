#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Inputs.hpp>
#include <GL/glew.h>
#include <iostream>
#include "../glimac/src/stb_image.h"
#include <glimac/Skybox.hpp>

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

int width = 800;
int height = 600;

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
    GLuint skyTxt = sky.genSkybox();
    
    FreeflyCamera cam; 

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            inputs(e,cam);
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        skyboxProgram.m_Program.use();
        glDepthFunc(GL_LEQUAL);
        glm::mat4 Projection = glm::perspective(glm::radians(70.f),float(width/height),0.1f,100.f);
        glm::mat4 View = cam.getViewMatrix();;

        glUniformMatrix4fv(skyboxProgram.uVMatrix, 1, GL_FALSE, glm::value_ptr(View));
        glUniformMatrix4fv(skyboxProgram.uPMatrix, 1, GL_FALSE, glm::value_ptr(Projection));

        sky.renderSkybox(skyTxt);

        glDepthFunc(GL_LESS);


        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}