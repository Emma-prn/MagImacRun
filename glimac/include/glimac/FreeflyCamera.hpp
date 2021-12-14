#pragma once

#include <vector>

#include "SDLWindowManager.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>

namespace glimac {

class FreeflyCamera {
    private: 
        glm::vec3 m_Position;
        float m_fPhi;
        float m_fTheta; 
        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;  

        void computeDirectionVectors() {
            float theta = glm::radians(m_fTheta); 
            float phi = glm::radians(m_fPhi);
            
            m_FrontVector = glm::vec3(  cos(theta) * sin(theta), 
                                        sin(theta),
                                        cos(theta) * cos(phi));

            m_LeftVector = glm::vec3(   sin(phi + M_PI/2), 
                                        0, 
                                        cos(phi + M_PI/2)); 
            
            m_UpVector = glm::cross(m_FrontVector, m_LeftVector);

        }

    public: 
        FreeflyCamera()
        {
            m_Position = glm::vec3(0, 0, 0);
            m_fPhi = M_PI; 
            m_fTheta = 0; 
            computeDirectionVectors();
        }

        void moveFront(float t); 
        void moveLeft(float t);

        void rotateLeft(float degrees); 
        void rotateUp(float degrees); 

        glm::mat4 getViewMatrix() const;
};
    
}