#pragma once
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <graphics/case.hpp>


/*! \struct TileProgram
 *  \brief Créer un programme permettant de charger les shaders utilisés et récupérer les emplacements des différentes variables uniformes
 *
 */
struct TileProgram {
    glimac::Program m_Program;

    GLint uPMatrix;
    GLint uVMatrix;
    GLuint uPos;
    GLuint uTile;

    TileProgram(const glimac::FilePath& applicationPath):
        m_Program(glimac::loadProgram(applicationPath.dirPath() + "shaders/tile.vs.glsl",
                              applicationPath.dirPath() + "shaders/tile.fs.glsl")) {
        uPMatrix = glGetUniformLocation(m_Program.getGLId(), "projection");
        uVMatrix = glGetUniformLocation(m_Program.getGLId(), "view");
        uPos = glGetUniformLocation(m_Program.getGLId(), "matPos");                  
        uTile = glGetUniformLocation(m_Program.getGLId(), "tile");
    }
};

/*! \class Tile
 *  \brief Représente une case terrain du parcours
 *
 */
class Tile : public Case
{
private:
    GLuint tileVAO;
    GLuint tileVBO;
    GLuint tileEBO;
    GLuint tileText;
    glm::vec2 tilePos;
    TileProgram tileProgram;
public:
    Tile(glm::vec2 tPos, const glimac::FilePath& applicationPath);
    ~Tile();
    void draw(glm::mat4 view, glm::mat4 proj) override;
    glm::vec2 getPos();
};