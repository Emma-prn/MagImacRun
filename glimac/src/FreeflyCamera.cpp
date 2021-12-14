#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/FreeflyCamera.hpp"

namespace glimac {


void FreeflyCamera::moveFront(float t){
    m_Position += t * m_FrontVector; 
}

void FreeflyCamera::moveLeft(float t){
    m_Position += t * m_LeftVector;
}

void FreeflyCamera::rotateLeft(float degrees){
    m_fPhi += glm::radians(degrees);
    computeDirectionVectors();
}

void FreeflyCamera::rotateUp(float degrees){
    m_fTheta += glm::radians(degrees);
    computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const {

    return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}


}
