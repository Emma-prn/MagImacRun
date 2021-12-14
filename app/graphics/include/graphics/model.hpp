/*#pragma once

#include <vector>
#include <map>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <graphics/shader.hpp>
#include <graphics/slice.hpp>

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

struct draw_instance {
  glm::mat4 transform;
  glm::vec3 color;
};

struct vertex {
  glm::vec3 position;
  glm::vec2 tex_coords;
  glm::vec3 normal;
};

class model {

  struct mesh {
    size_t indices_begin;
    size_t indices_end;
    GLuint texture;
  };

  GLuint m_vao;
  GLuint m_vertices_vbo;
  GLuint m_instances_vbo;
  GLuint m_ebo;

  std::map<std::string, GLuint> m_textures;
  std::vector<vertex> m_vertices;
  std::vector<GLuint> m_indices;
  std::vector<mesh> m_meshes;

  std::string m_directory;

  void load_node(const aiNode *node, const aiScene *scene);
  mesh load_mesh(const aiMesh *mesh, const aiScene *scene);
  GLuint load_material(const aiMaterial *material);
  GLuint load_texture(const std::string& texture_path);

  public:
    model(const std::string& obj_path, shader&);
    model(std::vector<vertex> vertices, std::vector<GLuint> indices, const std::string& texture_path);

    void draw(slice<draw_instance>);
};*/