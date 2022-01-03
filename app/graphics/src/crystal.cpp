#include <graphics/crystal.hpp> 
#include <graphics/genText.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <GL/gl.h>

Crystal::Crystal(GLfloat radius, GLsizei discLat, GLsizei discLong, glm::vec2 position, const glimac::FilePath& applicationPath)
    :m_nVertexCount(0), crystalProgram(applicationPath), crystalPos(position) {
        build(radius, discLat, discLong);
        glGenBuffers(1,&crystalVBO);
        glBindBuffer(GL_ARRAY_BUFFER,crystalVBO);
        glBufferData(GL_ARRAY_BUFFER, (this->getVertexCount())*sizeof(ShapeVertex), this->getDataPointer(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,0);

        glGenVertexArrays(1,&crystalVAO);
        glBindVertexArray(crystalVAO);
        glBindBuffer(GL_ARRAY_BUFFER,crystalVBO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex),(void*) offsetof(ShapeVertex,position)); 
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex),(void*) offsetof(ShapeVertex,normal)); 
        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(ShapeVertex),(void*) offsetof(ShapeVertex,texCoords));
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);

        crystalText = chargeTexture("../assets/textures/tiles/obsidian.png");
}

void Crystal::build(GLfloat r, GLsizei discLat, GLsizei discLong) {

    GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
    GLfloat dPhi = 2 * glm::pi<float>() * rcpLat, dTheta = glm::pi<float>() * rcpLong;
    
    std::vector<ShapeVertex> data;
    
    // Construit l'ensemble des vertex
    for(GLsizei j = 0; j <= discLong; ++j) {
        GLfloat cosTheta = cos(-glm::pi<float>() / 2 + j * dTheta);
        GLfloat sinTheta = sin(-glm::pi<float>() / 2 + j * dTheta);
        
        for(GLsizei i = 0; i <= discLat; ++i) {
            ShapeVertex vertex;
            
            vertex.texCoords.x = i * rcpLat;
            vertex.texCoords.y = 1.f - j * rcpLong;

            vertex.normal.x = sin(i * dPhi) * cosTheta;
            vertex.normal.y = sinTheta;
            vertex.normal.z = cos(i * dPhi) * cosTheta;
            
            vertex.position = r * vertex.normal;
            
            data.push_back(vertex);
        }
    }

    m_nVertexCount = discLat * discLong * 6;
    
    GLuint idx = 0;
    for(GLsizei j = 0; j < discLong; ++j) {
        GLsizei offset = j * (discLat + 1);
        for(GLsizei i = 0; i < discLat; ++i) {
            m_Vertices.push_back(data[offset + i]);
            m_Vertices.push_back(data[offset + (i + 1)]);
            m_Vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
            m_Vertices.push_back(data[offset + i]);
            m_Vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
            m_Vertices.push_back(data[offset + i + discLat + 1]);
        }
    }
}

void Crystal::crystalDraw(glm::mat4 view, glm::mat4 proj, glimac::SDLWindowManager &windowManager){
    crystalProgram.m_Program.use();
    glm::vec3 lightColor = glm::vec3(1.f,1.f,1.f);
    glm::vec3 lightPos = glm::vec3(0.5f,0.5f,0.5f);
    glm::vec3 camPos = glm::vec3(5.f,0.5f,1.f);

    glm::mat4 crystalMMatrix = glm::rotate(glm::mat4(1.), windowManager.getTime(), glm::vec3(0, 1, 0));
    glm::mat4 crystalMVMatrix = view*crystalMMatrix;
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(crystalMVMatrix));

    //Lumière
    glUniform3fv(crystalProgram.uLightColor, 1, glm::value_ptr(lightColor));
    glUniform3fv(crystalProgram.uLightPos, 1, glm::value_ptr(lightPos));
    glUniform3fv(crystalProgram.uCamPos, 1, glm::value_ptr(camPos));
        
    //Matrices
    glUniformMatrix4fv(crystalProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(crystalMVMatrix));
    glUniformMatrix4fv(crystalProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniformMatrix4fv(crystalProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(proj * crystalMVMatrix));
    glUniform1i(crystalProgram.uTexture, 0);
    glBindVertexArray(crystalVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, crystalText);
    glDrawArrays(GL_TRIANGLES, 0, this->getVertexCount());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);    
    glBindVertexArray(0);
}