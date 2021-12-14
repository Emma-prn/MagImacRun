#include <glimac/Skybox.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "stb_image.h"

Skybox::Skybox()
    :skyboxVAO(0),skyboxVBO(0),skyboxEBO(0),cubeMapText(0)
{};

GLuint Skybox::genSkybox(){
    float skyboxVertices[] = {
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f 
    };

    uint skyboxIndices[] = {
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

    glGenVertexArrays(1,&skyboxVAO);
    glGenBuffers(1,&skyboxVBO);
    glGenBuffers(1,&skyboxEBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    std::string facesCubeMap[6] = {
        "../assets/sky/posx.jpg",
        "../assets/sky/negx.jpg",
        "../assets/sky/posy.jpg",
        "../assets/sky/negy.jpg",
        "../assets/sky/posz.jpg",
        "../assets/sky/negz.jpg"
    };

    glGenTextures(1,&cubeMapText);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapText);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (size_t i = 0; i < 6; i++)
    {
        int widthF, heightF;
        unsigned char* data = stbi_load(facesCubeMap[i].c_str(), &widthF, &heightF, nullptr, 0);
        if (data)
        {
            stbi_set_unpremultiply_on_load(false);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X +i, 0, GL_RGB, widthF, heightF, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Failed to load texture : " << facesCubeMap[i] << std::endl;
            stbi_image_free(data);
        }
        
    }

    return cubeMapText;

};

void Skybox::renderSkybox(GLuint textID){
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textID);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
}

Skybox::~Skybox(){};