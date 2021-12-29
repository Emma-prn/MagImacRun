#pragma once
#include <glimac/glm.hpp>

class cameraA
{
private:
    
public:
    virtual void panVar(float variationPan);
    virtual void tiltVar(float variationTilt);
    virtual glm::mat4 getView(glm::vec3 PlayerPos);
};