#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <vector>

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct CrystalProgram {
    glimac::Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uLightColor;
    GLint uLightPos;
    GLuint uCamPos;

    CrystalProgram(const glimac::FilePath& applicationPath):
        m_Program(glimac::loadProgram(applicationPath.dirPath() + "shaders/crystal.vs.glsl",
                              applicationPath.dirPath() + "shaders/crystal.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "utexture");
        uLightColor = glGetUniformLocation(m_Program.getGLId(), "lightColor");
        uLightPos = glGetUniformLocation(m_Program.getGLId(), "lightPos");
        uCamPos = glGetUniformLocation(m_Program.getGLId(), "camPos");
    }
};

class Crystal
{
    void build(GLfloat radius, GLsizei discLat, GLsizei discLong);
private:
    std::vector<ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount;
    GLuint crystalVAO;
    GLuint crystalVBO;
    GLuint crystalText;
    CrystalProgram crystalProgram;
public:
    Crystal(GLfloat radius, GLsizei discLat, GLsizei discLong, const glimac::FilePath& applicationPath);

    // Renvoit le pointeur vers les données
    const ShapeVertex* getDataPointer() const {
        return &m_Vertices[0];
    }
    
    // Renvoit le nombre de vertex
    GLsizei getVertexCount() const {
        return m_nVertexCount;
    }

    void crystalDraw(glm::mat4 view, glm::mat4 proj, glimac::SDLWindowManager windowManager);
};