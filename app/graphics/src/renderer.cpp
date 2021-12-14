/*#include <graphics/renderer.hpp>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

renderer::renderer(std::shared_ptr<shader> shd) : shd(shd) {
}

mesh_id renderer::register_mesh(const std::vector<vertex>& mesh, const std::string& texture_path) {
  std::vector<GLuint> indices;
  indices.reserve(mesh.size());
  for (size_t i = 0; i < mesh.size(); ++i) {
    indices.push_back(i);
  }

  return register_mesh(mesh, indices, texture_path);
}

mesh_id renderer::register_mesh(const std::vector<vertex>& mesh, const std::vector<GLuint>& indices, const std::string& texture_path) {
  mesh_id ret;
  ret.i = next_free_mesh_id++;
  model_instance mod { .the_model = model(mesh, indices, texture_path), .instances = std::vector<draw_instance>() };
  model_instances.insert(std::pair(ret, mod));
  return ret;
}

mesh_id renderer::register_mesh_from_obj(const std::string& filename) {
  try {
    return model_by_name.at(filename);
  } catch (std::exception e) {
    mesh_id ret;
    ret.i = next_free_mesh_id++;

    model_by_name[filename] = ret;
    model_instance mod { .the_model = model(filename, *shd), .instances = std::vector<draw_instance>() };
    model_instances.insert(std::pair(ret, mod));

    return ret;
  }
}

void renderer::draw(mesh_id id, glm::vec3 position, glm::vec3 color) {
  glm::mat4 transform = glm::translate(position);
  model_instances.at(id).instances.push_back(draw_instance { .transform = transform, .color = color });
}

void renderer::draw(mesh_id id, const std::vector<glm::vec3>& positions, glm::vec3 color) {
  std::vector<draw_instance>& list = model_instances.at(id).instances;
  size_t old_size = list.size();
  list.resize(list.size() + positions.size());
  std::transform(positions.begin(), positions.end(), &list[old_size], [&](glm::vec3 v) { return draw_instance { .transform = glm::translate(v), .color = color }; });
}

void renderer::draw_scaled(mesh_id id, glm::vec3 position, glm::vec3 scale, glm::vec3 color) {
  glm::mat4 transform = glm::translate(position) * glm::scale(scale);
  model_instances.at(id).instances.push_back(draw_instance { .transform = transform, .color = color });
}

void renderer::draw_transformed(mesh_id id, glm::mat4 transform, glm::vec3 color) {
  model_instances.at(id).instances.push_back(draw_instance { .transform = transform, .color = color });
}

void renderer::render() {
  shd->use();
  for (std::map<mesh_id, model_instance>::iterator it = model_instances.begin(); it != model_instances.end(); ++it) {
    model_instance& inst = it->second;
    inst.the_model.draw(slice(inst.instances.data(), inst.instances.size()));
    inst.instances.clear();
  }
}*/
