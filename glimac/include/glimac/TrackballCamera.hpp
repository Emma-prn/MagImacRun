#pragma once

#include <vector>

#include "SDLWindowManager.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>

namespace glimac {

class TrackballCamera {
    private: 
        float m_fDistance;  // distance au centre de la scène
        float m_fAngleX;    // rotation haut-bas 
        float m_fAngleY;    // rotation gauche-droite 
    
    public: 
        TrackballCamera(float distance = 5.f, float angleX = 0.f, float angleY = 0.f) : m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY) {}

        void moveFront(float delta); 
        void rotateLeft(float degrees);
        void rotateUp(float degrees); 

        glm::mat4 getViewMatrix() const;
};
    
}