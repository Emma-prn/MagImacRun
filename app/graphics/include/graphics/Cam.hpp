#pragma once

#include <glimac/glm.hpp>
#include <geometry/joueur.hpp>
#include <graphics/cameraA.hpp> 

class CamTPers : public CamA
{
private:
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    float m_distanceToCenter;
    void computeDirectionVectors() {
        m_Position = glm::vec3(m_fPhi,m_fTheta,m_distanceToCenter);
    };
public:
    CamTPers()
        :m_Position(glm::vec3(0.,2.,0.)),m_fPhi(0),m_fTheta(glm::pi<float>()),m_distanceToCenter(2)
    {
        computeDirectionVectors();
    };
    ~CamTPers(){};
    void moveFront(float zoom){
        if ((canZoomIn() && zoom > 0) || (canZoomOut() && zoom < 0))
        {
            m_distanceToCenter += zoom;
            computeDirectionVectors();
        }
    };
    void rotateLeft(float degrees) {
        m_fPhi += glm::radians(degrees);
        computeDirectionVectors();
    };
    void rotateUp(float degrees) {
        m_fTheta += glm::radians(degrees);
        computeDirectionVectors();
    };

    bool canZoomIn(){
        return m_distanceToCenter < 5.f;
    }

    bool canZoomOut(){
        return m_distanceToCenter > 0.2f;
    }

    float getLeft(){return m_fPhi;};
    float getUp(){return m_fTheta;};
    float getDist(){return m_distanceToCenter;};
    glm::mat4 getViewMatrix(geo::Joueur joueur) const {
        glm::vec4 posJouCol = glm::column(joueur.getPosJou(),3);
        glm::vec3 posJou = glm::vec3(posJouCol.x, posJouCol.y, posJouCol.z);
        return glm::lookAt(m_Position+posJou,posJou,glm::vec3(0.,1.,0.));
    };
};