#include <graphics/camera.hpp>

glm::mat4 camera::view() {
  glm::vec3 dir = glm::normalize(target - eye);
  glm::vec3 up = glm::cross(glm::cross(dir, glm::vec3(0, 1, 0)), dir);
  glm::mat4 look_at = glm::lookAt(eye, target, up);
  return look_at;
}

glm::mat4 camera::projection() {
  glm::mat4 perspective = glm::perspective(glm::radians(fov), screen_width/screen_height, near, far);
  return perspective;
}

glm::vec3 camera::position() {
  return eye;
}

void camera::move_to(float pos) {
  eye += pos*target;
}

void camera::look_at(glm::vec3 t) {
  target = t;
}

void camera::set_screen_dimensions(float sw, float sh) {
  screen_width = sw;
  screen_height = sh;
}

glm::vec3 camera::billboard_normal() {
  return glm::cross(glm::vec3(0, 0, 1), target);
}

camera::camera(float near, float far, float fov)
  : eye(0)
  , target(glm::vec3(0.,0.,1.))
  , near(near)
  , far(far)
  , fov(fov)
  , screen_width(800)
  , screen_height(600)
{
}
