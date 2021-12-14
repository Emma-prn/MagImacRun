#pragma once

#include "glm.hpp"

class FreeflyCamera
{
private:
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;
    void computeDirectionVectors() {
        m_FrontVector = glm::vec3(glm::cos(m_fTheta)*glm::sin(m_fPhi),glm::sin(m_fTheta),glm::cos(m_fTheta)*glm::cos(m_fPhi));
        m_LeftVector = glm::vec3(glm::sin(m_fTheta+(glm::pi<float>()/2)),0,glm::cos(m_fTheta+(glm::pi<float>()/2)));
        m_UpVector = glm::vec3(glm::cross(m_FrontVector,m_LeftVector));
    };
public:
    FreeflyCamera()
        :m_Position(0,0,0),m_fTheta(glm::pi<float>()),m_fPhi(0)
    {computeDirectionVectors();};
    ~FreeflyCamera(){};
    void moveLeft(float t){m_Position += t*m_LeftVector;};
    void moveFront(float t){m_Position += t*m_FrontVector;};
    void rotateLeft(float degrees){
        m_fPhi += degrees;
        computeDirectionVectors();
    };
    void rotateUp(float degrees){
        m_fTheta += degrees;
        computeDirectionVectors();
    };
    float getLeft(){return m_fPhi;};
    float getUp(){return m_fTheta;};
    glm::mat4 getViewMatrix() const {return glm::lookAt(m_Position,m_Position+m_FrontVector,m_UpVector);};
};