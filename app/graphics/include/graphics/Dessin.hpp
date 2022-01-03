#pragma once

#include <glimac/Program.hpp>
#include <glimac/Objet.hpp>
#include <glimac/Texture.hpp>
#include <glimac/Joueur.hpp>

using namespace glimac;

class Dessin{

    private :

    GLuint vbo;
    GLuint vao;
    Objet& m_objet;

    void loadVao();
    void loadVbo(Objet &objet);
    void envoiVertex();

    public :

    Program m_Program;
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    Dessin(const FilePath& chemin, const char* shadersVS, const char* shadersFS, Objet& objet);
    ~Dessin(){
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void draw(Texture& texture, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);
    void draw(GLuint texture, glm::mat4 globalMVMatrix, glm::mat4 projMatrix);

};
