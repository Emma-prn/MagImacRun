#include <graphics/genText.hpp>
#include <glimac/Image.hpp>
#include <cstdlib>
#include <iostream>

GLuint chargeTexture(char* filepath){
    std::unique_ptr<glimac::Image> img = glimac::loadImage(filepath);
    if (!img)
    {
        std::cerr << "Error Image Not Found" << std::endl;
    }
    
    GLuint textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img->getWidth(),img->getHeight(),0,GL_RGBA,GL_FLOAT,img->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);
    return textureID;
}