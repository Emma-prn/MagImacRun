#include <graphics/Dessin.hpp>

Dessin::Dessin(const FilePath& chemin, const char* shadersVS, const char* shadersFS, Objet& objet)
    :m_Program(loadProgram(chemin.dirPath() + "shaders/"+shadersVS,
                           chemin.dirPath() + "shaders/"+shadersFS)),
    m_objet(objet)
{
    uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
    uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");

    loadVbo(m_objet);
    loadVao();
    envoiVertex();
};

void Dessin::loadVao(){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Dessin::loadVbo(Objet &objet){
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, objet.getVertexCount()*sizeof(ShapeVertex), objet.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Dessin::envoiVertex(){
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    const GLuint VERTEX_ATTR_NORMALE = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMALE);
    const GLuint VERTEX_ATTR_TEXCOORD = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORD);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Dessin::draw(Texture& texture, glm::mat4 globalMVMatrix, glm::mat4 projMatrix){
    glBindVertexArray(vao);
    m_Program.use();
    glUniform1i(uTexture, 0);

    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(globalMVMatrix));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * globalMVMatrix)); 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.m_texture);
    glDrawArrays(GL_TRIANGLES, 0, m_objet.getVertexCount());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Dessin::draw(GLuint texture, glm::mat4 globalMVMatrix, glm::mat4 projMatrix){
    glBindVertexArray(vao);
    m_Program.use();
    glUniform1i(uTexture, 0);

    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(globalMVMatrix));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * globalMVMatrix)); 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, m_objet.getVertexCount());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
