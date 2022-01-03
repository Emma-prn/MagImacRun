#include <glimac/Texture.hpp>


using namespace glimac;
  
Texture::Texture(const FilePath& chemin, const char* image)
{
    // Chargement de l'image
    std::unique_ptr<Image> textureImage = loadImage(chemin.dirPath()+"assets/textures/"+image);
    if(!image) {
        std::cerr << "erreur de chargement de l'image" << std::endl;
    }

    // Génération de la texture
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->getWidth(), textureImage->getHeight(), 0, GL_RGBA, GL_FLOAT, textureImage->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}


