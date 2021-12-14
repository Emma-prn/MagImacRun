#pragma once

#include "glm.hpp"

class TrackballCamera
{
private:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;
public:
    TrackballCamera(const float distance = 5., const float angleX = 0., const float angleY = 0.)
        :m_fDistance(distance),m_fAngleX(angleX),m_fAngleY(angleY)
    {};
    void moveFront(float delta){ m_fDistance -= delta; };
    void rotateLeft(float degrees){ m_fAngleY += degrees; };
    void rotateUp(float degrees) { m_fAngleX += degrees; };
    float getAngleY(){return m_fAngleY;};
    float getAngleX(){return m_fAngleX;};
    float getDistance(){return m_fDistance;};
    glm::mat4 getViewMatrix() const {
        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, m_fDistance));
        viewMatrix = glm::rotate(viewMatrix, m_fAngleX, glm::vec3(1, 0, 0));
        viewMatrix = glm::rotate(viewMatrix, m_fAngleY, glm::vec3(0, 1, 0));
        return viewMatrix;
    };
    ~TrackballCamera(){};
};