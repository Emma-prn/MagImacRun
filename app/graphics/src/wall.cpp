#include <graphics/wall.hpp>
#include <glimac/Image.hpp>
#include <iostream>
#include <vector>
#include <GL/gl.h>

Wall::Wall(glm::vec2 tPos, const glimac::FilePath& applicationPath)
    :wallPos(tPos), wallProgram(applicationPath)
{
    GLfloat wallVertices[] = {
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
    };

    uint wallIndices[] = {
        1, 2, 6,
        6, 5, 1,
        0, 4, 7,
        7, 3, 0,
        4, 5, 6,
        6, 7, 4,
        0, 3, 2,
        2, 1, 0,
        0, 1, 5,
        5, 4, 0,
        3, 7, 6,
        6, 2, 3
    };

    glGenVertexArrays(1,&wallVAO);
    glGenBuffers(1,&wallVBO);
    glGenBuffers(1,&wallEBO);
    glBindVertexArray(wallVAO);
    glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), &wallVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wallEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wallIndices), &wallIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    std::unique_ptr<glimac::Image> imgW = glimac::loadImage("../assets/textures/tiles/wall.png");
    if (!imgW)
    {
        std::cerr << "Error Image Not Found" << std::endl;
    }

    glGenTextures(1,&wallText);
    glBindTexture(GL_TEXTURE_CUBE_MAP, wallText);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (size_t i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X +i,0,GL_RGBA,imgW->getWidth(),imgW->getHeight(),0,GL_RGBA,GL_FLOAT,imgW->getPixels());
    }
};

void Wall::draw(glm::mat4 view, glm::mat4 proj){
        wallProgram.m_Program.use();
        const auto wallPos = getPos();
        auto pos2 = glm::translate(glm::mat4(1.f), glm::vec3(wallPos.x,0.f,wallPos.y));
        glUniformMatrix4fv(wallProgram.uVMatrix, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(wallProgram.uPMatrix, 1, GL_FALSE, glm::value_ptr(proj));
        glUniformMatrix4fv(wallProgram.uPos, 1, GL_FALSE, glm::value_ptr(pos2));
        glUniform1i(wallProgram.uCube,0);
        glBindVertexArray(wallVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, wallText);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
}

Wall::~Wall(){};

glm::vec2 Wall::getPos(){
    return wallPos;
};