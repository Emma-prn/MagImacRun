#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Inputs.hpp>

void inputs(SDL_Event e, FreeflyCamera cam){
    switch (e.type)
    {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
                case SDLK_z:
                    std::cout << "touche presse z" << std::endl;
                    cam.moveFront(0.1f);
                    break;
                case SDLK_s:
                    std::cout << "touche presse s" << std::endl;
                    cam.moveFront(-0.1f);
                    break;
                case SDLK_q:
                    std::cout << "touche presse q" << std::endl;
                    cam.moveLeft(0.1f);
                    break;
                case SDLK_d:
                    std::cout << "touche presse d" << std::endl;
                    cam.moveLeft(-0.1f);
                    break;
                default:
                    break;
            }
            break;
        case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                switch (e.button.button){
                    case SDL_BUTTON_LEFT:
                        cam.rotateUp(glm::radians(float(e.motion.yrel)));
                        cam.rotateLeft(glm::radians(float(e.motion.xrel)));
                        break;
                    default:
                        break;
                }
                break;
        default:
            break;
    }
};