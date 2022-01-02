#pragma once
#include <glimac/glm.hpp>
#include <geometry/spatial_object.hpp>

namespace geo {
    class Joueur
    {
    private:
        spatial_object posOriJoueur;
    public:
        Joueur(glm::vec2 joueurOrigin);
        ~Joueur();
        void turnRight();
        void turnLeft();
        void move();
        void jump();
        void slide();
        glm::mat4 getPosJou();
    };
}