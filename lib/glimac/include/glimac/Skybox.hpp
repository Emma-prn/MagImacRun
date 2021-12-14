#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

class Skybox
{
private:
    GLuint skyboxVAO;
    GLuint skyboxVBO;
    GLuint skyboxEBO;
    GLuint cubeMapText;
    
public:
    Skybox();
    GLuint genSkybox();
    void renderSkybox(GLuint textID);
    ~Skybox();
};