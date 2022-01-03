#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Rectangle.hpp"

namespace glimac {

void Rectangle::build(GLfloat height, GLfloat width, GLfloat depth) {

    static const GLfloat position[] = {

        // face avant
        -width, -height, 0, //0
        width, -height, 0, //1
        width,  height, 0, //2

        width,  height, 0, //2
        -width,  height, 0, //3
        -width, -height, 0, //0

        // face arrière
        width, -height, 0, //5
        -width, -height, 0,//4
        -width,  height, 0, //7 

        -width,  height, 0, //7
        width, -height, 0, //5
        width,  height, 0, //6
       
    };

    static const GLfloat normale[] = {

        // face avant
        0, 0, -1, //0
        0, 0, -1, //1
        0, 0, -1, //2
        0, 0, -1, //3
        0, 0, -1, //2
        0, 0, -1, //3

        // face arrière
        0, 0, 1, //4
        0, 0, 1, //5
        0, 0, 1, //6
        0, 0, 1, //7 
        0, 0, 1, //6
        0, 0, 1, //7 
       
    };

    static const GLfloat texture[] = {

        // face avant
        
        0, 1, 9, //0
        1, 1, 9, //1
        1, 0, 9, //2

        1, 0, 9, //2
        0, 0, 9, //3        
        0, 1, 9, //0
/*
        // face arrière
        
        0, 1, 9, //5
        1, 1, 9, //4
        1, 0, 9, //7 

        1, 0, 9, //7
        0, 1, 9, //5
        0, 0, 9, //6
*/
    };


    std::vector<ShapeVertex> data;
    
    // Construit l'ensemble des vertex
    for(GLsizei i = 0; i <= 36; i+=3) {
        ShapeVertex vertex;

        vertex.position.x = position[i];
        vertex.position.y = position[i+1];
        vertex.position.z = position[i+2];

        vertex.normal.x = normale[i];
        vertex.normal.y = normale[i+1];
        vertex.normal.z = normale[i+2];

        vertex.texCoords.x = texture[i];
        vertex.texCoords.y = texture[i+1];
            
        data.push_back(vertex);
    }

    m_nVertexCount = 12;

    for(GLsizei i = 0; i < m_nVertexCount; ++i) {
        m_Vertices.push_back(data[i]);
    }

}

}
