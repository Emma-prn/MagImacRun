#pragma once
#include <glimac/glm.hpp>
#include <geometry/spatial_object.hpp>

namespace geo {
    class Joueur
    {
    private:
        spatial_object posOriJoueur;
        glm::vec2 direction;
    public:
        Joueur(glm::vec2 joueurOrigin);
        ~Joueur();
        void turnRight();
        void turnLeft();
        void move();
        void jump();
        void land();
        void slide();
        void standUp();
        void fall();
        bool isJumping();
        glm::mat4 getPosJou();
    };
}
