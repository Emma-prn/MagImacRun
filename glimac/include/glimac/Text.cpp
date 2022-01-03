#include "glimac/Text.hpp"

void Text::createText(SDL_Surface * destination)
{
    if (m_string.size()) 
    {    
        m_surface = TTF_RenderText_Solid(m_font, m_string.c_str(), m_color);
        // apply surface to la surface du menu
        if (destination) std::cout << "destination définie" << std::endl;
        applyToSurface(destination);
        SDL_FreeSurface(m_surface);
    }
}

void Text::loadFont(const char * linkFont)
{
    m_font = TTF_OpenFont(linkFont, 72);
    if (!m_font) std::cout << "Error loading font: " << TTF_GetError() << std::endl;
}

void Text::applyToSurface(SDL_Surface * destination)
{
    SDL_Rect rect; 
    rect.x = m_coordonnees.x;
    rect.y = m_coordonnees.y; 


    SDL_BlitSurface(m_surface,  // source
                    NULL, 
                    destination,// destination 
                    &rect); 
}

