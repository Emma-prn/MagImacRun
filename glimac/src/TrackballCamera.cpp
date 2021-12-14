#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/TrackballCamera.hpp"

namespace glimac {

void TrackballCamera::moveFront(float delta) 
{
    m_fDistance += delta;
}

void TrackballCamera::rotateLeft(float degrees) 
{
    m_fAngleX += glm::radians(degrees);
}

void TrackballCamera::rotateUp(float degrees) 
{
    m_fAngleY += glm::radians(degrees);
}

glm::mat4 TrackballCamera::getViewMatrix() const 
{
   glm::mat4 VM = glm::mat4(1);
   VM = glm::translate(VM, glm::vec3(0, 0, -m_fDistance));             // distance caméra
   VM = glm::rotate(VM, glm::radians(m_fAngleX), glm::vec3(0, 1, 0)); // rotation X
   VM = glm::rotate(VM, glm::radians(m_fAngleY), glm::vec3(1, 0, 0)); // rotation Y

   return VM;
}


}
