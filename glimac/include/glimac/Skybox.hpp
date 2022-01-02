#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>

/*! \struct ShaderProgram
 *  \brief Créer un programme permettant de charger les shaders utilisés et récupérer les emplacements des différentes variables uniformes
 *
 */
struct SkyboxProgram {
    glimac::Program m_Program;

    GLint uPMatrix;
    GLint uVMatrix;
    GLint uSky;

    SkyboxProgram(const glimac::FilePath& applicationPath):
        m_Program(glimac::loadProgram(applicationPath.dirPath() + "shaders/skybox.vs.glsl",
                              applicationPath.dirPath() + "shaders/skybox.fs.glsl")) {
        uPMatrix = glGetUniformLocation(m_Program.getGLId(), "projection");
        uVMatrix = glGetUniformLocation(m_Program.getGLId(), "view");
        uSky = glGetUniformLocation(m_Program.getGLId(), "skybox");
    }
};

class Skybox
{
private:
    GLuint skyboxVAO;
    GLuint skyboxVBO;
    GLuint skyboxEBO;
    GLuint cubeMapText;
    SkyboxProgram skyboxProgram;
    
public:
    Skybox(const glimac::FilePath& applicationPath);
    void renderSkybox(glm::mat4 view, glm::mat4 proj);
    ~Skybox();
};