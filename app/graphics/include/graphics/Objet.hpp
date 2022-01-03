#pragma once

#include <vector>
#include <glimac/ShapeVertex.hpp>

constexpr bool verbatim = false;

namespace glimac {
    
class Objet {

    public:

        Objet():m_nVertexCount(0){}
        Objet(Objet& objet):m_Vertices(objet.m_Vertices), m_nVertexCount(objet.m_nVertexCount){};

        virtual ~Objet(){};

        // Renvoit le pointeur vers les données
        const ShapeVertex* getDataPointer() const {
            return &m_Vertices[0];
        }
    
        // Renvoit le nombre de vertex
        GLsizei getVertexCount() const {
            return m_nVertexCount;
        }

        

    protected:

        virtual void build(GLfloat height, GLfloat width, GLfloat depth) = 0;
        
        std::vector<ShapeVertex> m_Vertices;
        GLsizei m_nVertexCount; // Nombre de sommets
    };
    
}
