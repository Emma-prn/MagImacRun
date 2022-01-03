#pragma once

#include <vector>
#include <glimac/ShapeVertex.hpp>
#include <include/graphics/Objet.hpp>

namespace glimac {
    
class Rectangle : public Objet{
    

public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Rectangle(GLfloat height, GLfloat width)
        :Objet()
    {
        build(height, width, 0); // Construction (voir le .cpp)
    }

    ~Rectangle(){};

protected: 
    // Alloue et construit les données (implantation dans le .cpp)
    void build(GLfloat height, GLfloat width, GLfloat depth) override;
};
    
}
