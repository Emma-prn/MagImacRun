#pragma once
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <graphics/case.hpp>

struct CubeProgram {
    glimac::Program m_Program;

    GLint uPMatrix;
    GLint uVMatrix;
    GLuint uPos;
    GLint uCube;

    CubeProgram(const glimac::FilePath& applicationPath):
        m_Program(glimac::loadProgram(applicationPath.dirPath() + "shaders/cube.vs.glsl",
                              applicationPath.dirPath() + "shaders/cube.fs.glsl")) {
        uPMatrix = glGetUniformLocation(m_Program.getGLId(), "projection");
        uVMatrix = glGetUniformLocation(m_Program.getGLId(), "view");
        uPos = glGetUniformLocation(m_Program.getGLId(), "matPos");
        uCube = glGetUniformLocation(m_Program.getGLId(), "cube");
    }
};

class Wall : public Case
{
private:
    GLuint wallVAO;
    GLuint wallVBO;
    GLuint wallEBO;
    GLuint wallText;
    glm::vec2 wallPos;
    CubeProgram wallProgram;
public:
    Wall(glm::vec2 tPos, const glimac::FilePath& applicationPath);
    ~Wall();
    void draw(glm::mat4 view, glm::mat4 proj) override;
    glm::vec2 getPos();
};
