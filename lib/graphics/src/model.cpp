#include <graphics/model.hpp>

#include <functional>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

model::model(const std::string& obj_path, shader& shd) {
  m_directory = obj_path.substr(0, obj_path.find_last_of('/'));
 
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vertices_vbo);
  glGenBuffers(1, &m_instances_vbo);
  glGenBuffers(1, &m_ebo);

  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertices_vbo);

  GLuint id = shd.attrib_location("position");
  if (id == -1) {
    std::cerr << "WARNING: 'position' is not an attribute for the shader used by the renderer.\n";
  }
  glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
  glEnableVertexAttribArray(id);

  id = shd.attrib_location("tex_coords");
  if (id == -1) {
    std::cerr << "WARNING: 'tex_coords' is not an attribute for the shader used by the renderer.\n";
  }
  glVertexAttribPointer(id, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, tex_coords));
  glEnableVertexAttribArray(id);

  id = shd.attrib_location("normal");
  if (id == -1) {
    std::cerr << "WARNING: 'normal' is not an attribute for the shader used by the renderer.\n";
  }
  glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
  glEnableVertexAttribArray(id);

  glBindBuffer(GL_ARRAY_BUFFER, m_instances_vbo);
  
  id = shd.attrib_location("instanceTransform");
  if (id == -1) {
    std::cerr << "WARNING: 'instanceTransform' is not an attribute for the shader used by the renderer.\n";
  }

  // mat4 ne peut pas être lié (trop gros), on le divise donc en 4 vec4
  
  for (int i = 0; i < 4; ++i) {
    glVertexAttribPointer(id+i, 4, GL_FLOAT, GL_FALSE, sizeof(draw_instance), (void*)(offsetof(draw_instance, transform) + i*sizeof(glm::vec4)));
    glEnableVertexAttribArray(id+i);
    glVertexAttribDivisor(id+i, 1);
  }

  id = shd.attrib_location("instanceColor");
  if (id == -1) {
    std::cerr << "WARNING: 'instanceColor' is not an attribute for the shader used by the renderer.\n";
  }
  glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, sizeof(draw_instance), (void*)offsetof(draw_instance, color));
  glEnableVertexAttribArray(id);
  glVertexAttribDivisor(id, 1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(obj_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
  if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
    std::cerr << "ERROR: cannot import model " << obj_path << "\n";
    std::cerr << "\tReason: " << importer.GetErrorString() << "\n";

    return;
  }

  load_node(scene->mRootNode, scene);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertices_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(vertex), m_vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

model::model(std::vector<vertex> vertices, std::vector<GLuint> indices, const std::string& texture_path)
  : m_vertices(vertices)
  , m_indices(indices)
{
  GLuint texture = load_texture(texture_path);
  m_meshes.push_back(mesh { .indices_begin = 0, .indices_end = m_indices.size(), .texture = texture });
}

void model::draw(slice<draw_instance> instances) {
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_instances_vbo);
  glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(draw_instance), instances.data(), GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertices_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  for (mesh m : m_meshes) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m.texture);

    glDrawElementsInstanced(
        GL_TRIANGLES,
        m.indices_end - m.indices_begin,
        GL_UNSIGNED_INT,
        (void*)(m.indices_begin * sizeof(GLuint)),
        instances.size());
  }
}

void model::load_node(const aiNode *node, const aiScene *scene) {
  for (size_t i = 0; i < node->mNumMeshes; ++i) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    m_meshes.push_back(load_mesh(mesh, scene));
  }

  for (size_t i = 0; i < node->mNumChildren; ++i) {
    load_node(node->mChildren[i], scene);
  }
}

model::mesh model::load_mesh(const aiMesh *mesh, const aiScene *scene) {
  GLuint vstart_index = m_vertices.size();
  GLuint istart_index = m_indices.size();
  for (size_t i = 0; i < mesh->mNumVertices; ++i) {
    vertex v;
    v.position.x = mesh->mVertices[i].x;
    v.position.y = mesh->mVertices[i].y;
    v.position.z = mesh->mVertices[i].z;

    if (mesh->HasNormals()) {
      v.normal.x = mesh->mNormals[i].x;
      v.normal.y = mesh->mNormals[i].y;
      v.normal.z = mesh->mNormals[i].z;
    }

    if (mesh->mTextureCoords[0]) {
      v.tex_coords.x = mesh->mTextureCoords[0][i].x;
      v.tex_coords.y = mesh->mTextureCoords[0][i].y;
    }

    m_vertices.push_back(v);
  }

  for (size_t i = 0; i < mesh->mNumFaces; ++i) {
    aiFace face = mesh->mFaces[i];
    for (size_t j = 0; j < face.mNumIndices; ++j) {
      m_indices.push_back(face.mIndices[j] + vstart_index);
    }
  }

  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
  GLuint texture_id = load_material(material);

  return model::mesh { .indices_begin = istart_index, .indices_end = istart_index + mesh->mNumVertices, .texture = texture_id };
}

GLuint model::load_material(const aiMaterial *material) {
  size_t count = material->GetTextureCount(aiTextureType_DIFFUSE);
  std::string tex_path;
  if (count > 0) {
    aiString str;
    material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
    tex_path = m_directory + '/' + str.C_Str();
  }

  return load_texture(tex_path);
}

GLuint model::load_texture(const std::string& tex_path) {
  try {
    return m_textures.at(tex_path);
  } catch (std::exception e) {


    GLuint ret;
    glGenTextures(1, &ret);
    glBindTexture(GL_TEXTURE_2D, ret);

    int width, height, nb_components;
    unsigned char *data = stbi_load(tex_path.c_str(), &width, &height, &nb_components, 0);
    if (data) {
      GLenum format;
      switch (nb_components) {
        case 1: format = GL_RED; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: break;
      }

      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

      stbi_image_free(data);
    } else {
      if (tex_path == "") {
        unsigned char data[] {
          255, 255, 255, 255
        };
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      } else {
        std::cerr << "Could not load texture " << tex_path << "\n";
        exit(-1);
      }
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_textures.insert(std::pair(tex_path, ret));

    return ret;
  }
}
