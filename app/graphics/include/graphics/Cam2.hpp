#pragma once
#include <cmath> 
#include <glimac/glm.hpp>
#include <geometry/joueur.hpp>
#include <graphics/cameraA.hpp> 

class CamFPers : public CamA
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
    CamFPers(geo::Joueur joueur)
        :m_fPhi(0),m_fTheta(glm::pi<float>())
    {
        glm::vec4 posJouCol = glm::column(joueur.getPosJou(),3);
        glm::vec3 posJou = glm::vec3(posJouCol.x, posJouCol.y+1, posJouCol.z);
        m_Position = posJou;
        computeDirectionVectors();
    };
    ~CamFPers(){};
    void moveLeft(float t){m_Position += t*m_LeftVector;};
    void moveFront(float t){m_Position += t*m_FrontVector;};
    void rotateLeft(float degrees){
        if ((canRotateLeft() && degrees < 0) || (canRotateRight() && degrees > 0))
        {
            m_fPhi += glm::radians(degrees);
            computeDirectionVectors();
        }
    };
    void rotateUp(float degrees){
        if ((canRotateUp() && degrees > 0) || (canRotateDown() && degrees < 0))
        {
            m_fTheta += glm::radians(degrees);
            computeDirectionVectors();
        }
    };

    bool canRotateUp(){
        return m_fTheta < M_PI + M_PI/10;
    };

    bool canRotateDown(){
        return m_fTheta > M_PI - M_PI/10;
    };

    bool canRotateLeft(){
        return m_fPhi > -M_PI/4;
    };

    bool canRotateRight(){
        return m_fPhi < M_PI/4;
    };

    float getLeft(){return m_fPhi;};
    float getUp(){return m_fTheta;};
    glm::mat4 getViewMatrix(geo::Joueur joueur) const {
        glm::vec4 posJouCol = glm::column(joueur.getPosJou(),3);
        glm::vec3 posJou = glm::vec3(posJouCol.x, posJouCol.y+1, posJouCol.z);
        return glm::lookAt(posJou,posJou+m_FrontVector,m_UpVector);
    };
};