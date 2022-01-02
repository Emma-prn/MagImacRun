#pragma once
#include <glimac/glm.hpp>
#include <geometry/joueur.hpp>

class CamA
{
private:
    
public:
    virtual void rotateLeft(float degrees) = 0;
    virtual void rotateUp(float degrees) = 0;
    virtual glm::mat4 getViewMatrix(geo::Joueur joueur) const = 0;
};