#include <geometry/spatial_object.hpp>
#include <geometry/joueur.hpp>

namespace geo {
    Joueur::Joueur(glm::vec2 joueurOrigin)
        :posOriJoueur(glm::translate(glm::mat4(1.f),glm::vec3(joueurOrigin.x, 0.f, joueurOrigin.y)))
    {};
    Joueur::~Joueur(){};
    void Joueur::turnRight(){
        posOriJoueur.rotate(glm::vec3(1.f,0.f,0.f),90);
    };
    void Joueur::turnLeft(){
        posOriJoueur.rotate(glm::vec3(1.f,0.f,0.f),-90);
    };
    void Joueur::move(){
        posOriJoueur.translate(glm::vec3(0.f,0.f,1.f));
    };
    void Joueur::jump(){

    };
    void Joueur::slide(){

    };
    glm::mat4 Joueur::getPosJou(){
        return posOriJoueur.global_transform();
    };
}