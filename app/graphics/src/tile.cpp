#include <graphics/tile.hpp>
#include <graphics/genText.hpp>
#include <iostream>
#include <vector>
#include <GL/gl.h>

Tile::Tile(glm::vec2 tPos, const glimac::FilePath& applicationPath)
    :tilePos(tPos), tileProgram(applicationPath)
{
    GLfloat tileVertices[] = {
        -0.5f, -0.5f,   0.f, 0.f, 
        -0.5f, 0.5f,    0.f, 1.f,
        0.5f, 0.5f,     1.f, 1.f,
        0.5f, -0.5f,    1.f, 0.f
    };

    uint tileIndices[] = {
        0, 2, 1, 
        0, 3, 2
    };

    glGenVertexArrays(1,&tileVAO);
    glGenBuffers(1,&tileVBO);
    glGenBuffers(1,&tileEBO);
    glBindVertexArray(tileVAO);
    glBindBuffer(GL_ARRAY_BUFFER, tileVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tileVertices), &tileVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tileEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tileIndices), &tileIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    tileText = chargeTexture("../assets/textures/tiles/ground.png");
};

Tile::~Tile(){};

void Tile::draw(glm::mat4 view, glm::mat4 proj) {
    tileProgram.m_Program.use();
    const auto tilePos = getPos();
    auto pos2 = glm::translate(glm::mat4(1.f), glm::vec3(tilePos.x,0.f,tilePos.y));
    glUniformMatrix4fv(tileProgram.uVMatrix, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(tileProgram.uPMatrix, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(tileProgram.uPos, 1, GL_FALSE, glm::value_ptr(pos2));
    glUniform1i(tileProgram.uTile,0);
    glBindVertexArray(tileVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tileText);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
};

glm::vec2 Tile::getPos(){
    return tilePos;
}