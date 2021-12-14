#include <geometry/spatial_object.hpp>
#include <iostream>

spatial_object::spatial_object(glm::mat4 transform) : m_transform(transform) {}

glm::mat4 spatial_object::global_transform() const {
  return m_transform;
}

const glm::mat4& spatial_object::local_transform() const {
  return m_transform;
}

void spatial_object::move_to(glm::vec3 position) {
  m_transform[3][0] = position[0];
  m_transform[3][1] = position[1];
  m_transform[3][2] = position[2];
}

void spatial_object::translate(glm::vec3 delta) {
  m_transform = glm::translate(delta) * m_transform;
}

void spatial_object::translate_xz(glm::vec2 delta) {
  translate(glm::vec3(delta.x, 0, delta.y));
}

void spatial_object::rotate(glm::vec3 axis, float angle) {
  m_transform = glm::rotate(m_transform, angle, axis);
}

void spatial_object::set_transform(glm::mat4 m) {
  m_transform = m;
}
