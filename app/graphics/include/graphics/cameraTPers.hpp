#pragma once
#include <graphics/cameraA.hpp>
#include <cmath>

class cameraTPers : public cameraA
{
private:
    float m_pan = 0.f;
    float m_tilt = 0.4f;
    float m_zoom = 5.f;
    float RotationSpeed = 0.3f;
    float ZoomSpeed = 0.2f;
public:
    cameraTPers();
    ~cameraTPers();
    void panVar(float variationPan);
    void tiltVar(float variationTilt);
    bool canTiltUp();
    bool canTiltDown();
    glm::mat4 getView(glm::vec3 PlayerPos);
};

cameraTPers::cameraTPers()
{
}

cameraTPers::~cameraTPers()
{
}

void cameraTPers::panVar(float variationPan){
    m_pan += variationPan*RotationSpeed;
}

void cameraTPers::tiltVar(float variationTilt){
    if ((canTiltUp() && variationTilt > 0) ||(canTiltDown() && variationTilt < 0))
    {
        m_tilt += variationTilt*RotationSpeed;
    }
}

bool cameraTPers::canTiltUp(){
    return m_tilt > 0;
}

bool cameraTPers::canTiltDown(){
    return m_tilt < M_PI/4 ;
}

glm::mat4 cameraTPers::getView(glm::vec3 PlayerPos){
    glm::vec3 dir = glm::normalize(target - eye);
    glm::vec3 up = glm::cross(glm::cross(dir, glm::vec3(0, 1, 0)), dir);
    glm::mat4 look_at = glm::lookAt(eye, target, up);
    return look_at;
}