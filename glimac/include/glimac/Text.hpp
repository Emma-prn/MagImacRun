#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <glimac/glm.hpp>


class Text 
{
private: 
    std::string  m_string; 
    SDL_Color    m_color;
    int          m_size;
    
    SDL_Surface* m_surface;
    TTF_Font*    m_font;

    glm::vec2   m_coordonnees; 

    void loadFont(const char * linkFont); 
    void createText(SDL_Surface * destination);
    void applyToSurface(SDL_Surface * destination);

public: 
    Text(const std::string &string, const SDL_Color &color, 
         const int &size,           const glm::vec2 &pos,
         SDL_Surface* destination)
        : m_string(string), m_color(color), 
          m_size(size), m_coordonnees(pos)
        {
            loadFont("assets/fonts/NunitoSans-Bold.ttf");
            createText(destination);
        }

    ~Text() = default;

    void iniText2D(const char * texturePath);
    void printText2D(const char * text, int x, int y, int size);
    void cleanupText2D();
    
};