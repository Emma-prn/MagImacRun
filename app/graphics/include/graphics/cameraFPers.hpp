#pragma once
#include <graphics/cameraA.hpp>

class cameraFPers : public cameraA
{
private:
    float m_pan = 0.f;
    float m_tilt = 0.4f;
    float RotationSpeed = 0.3f;
    float ZoomSpeed = 0.2f;
public:
    cameraTPers();
    ~cameraTPers();
    void panVar(float variationPan);
    void tiltVar(float variationTilt);
    bool canPanRight();
    bool canPanLeft();
    bool canTiltUp();
    bool canTiltDown();
    glm::mat4 getView(glm::vec3 PlayerPos);
};

cameraFPers::cameraTPers()
{
}

cameraFPers::~cameraTPers()
{
}

void cameraFPers::panVar(float variationPan){
    if ((canPanRight() && variationPan > 0) ||(canPanLeft() && variationPan < 0))
    {
        m_pan += variationPan*RotationSpeed;
    }
}

void cameraFPers::tiltVar(float variationTilt){
    if ((canTiltUp() && variationTilt > 0) ||(canTiltDown() && variationTilt < 0))
    {
        m_tilt += variationTilt*RotationSpeed;
    }
}

bool cameraFPers::canPanRight(){
    return m_pan < M_PI/2;
}

bool cameraFPers::canPanLeft(){
    return m_pan > -M_PI/2;
}

bool cameraFPers::canTiltUp(){
    return m_tilt > M_PI/4;
}

bool cameraFPers::canTiltDown(){
    return m_tilt < -M_PI/4 ;
}

glm::mat4 cameraFPers::getView(glm::vec3 PlayerPos){
    glm::vec3 dir = glm::normalize(target - eye);
    glm::vec3 up = glm::cross(glm::cross(dir, glm::vec3(0, 1, 0)), dir);
    glm::mat4 look_at = glm::lookAt(PlayerPos, target, up);
    return look_at;
}