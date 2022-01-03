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
        posOriJoueur.translate(glm::vec3(0.f,0.f,-0.01f));
    };
    void Joueur::jump(){
        posOriJoueur.translate(glm::vec3(0.f,2.f,0.f));
    };
    void Joueur::land(){
        posOriJoueur.translate(glm::vec3(0.f,-2.f,0.f));
    };
    void Joueur::slide(){
        posOriJoueur.translate(glm::vec3(0.f,-0.5f,0.f));
    };
    void Joueur::standUp(){
        posOriJoueur.translate(glm::vec3(0.f,0.5f,0.f));
    };
    void Joueur::fall(){
        glm::vec4 posJouCol = glm::column(getPosJou(),3);
        if(posJouCol.y > -10.f){
            posOriJoueur.translate(glm::vec3(0.f,-0.5f,0.f));
        }
    };
    bool Joueur::isJumping(){
        glm::vec4 posJouCol = glm::column(getPosJou(),3);
        return posJouCol.y > 0;
    };
    glm::mat4 Joueur::getPosJou(){
        return posOriJoueur.global_transform();
    };
}