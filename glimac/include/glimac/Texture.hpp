#pragma once

#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <iostream>

namespace glimac {

class Texture{

    public :

    GLuint m_texture;
    Texture(const FilePath& chemin, const char* image);
    ~Texture(){}
    
};

}
