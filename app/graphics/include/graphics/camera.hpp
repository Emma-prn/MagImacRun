#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

/*! \class camera
 *  \brief Représente une caméra dans un monde 3D
 *
 *  TODO: devrait être un spatial_object
 */
class camera {
  glm::vec3 eye;
  glm::vec3 target;

  float near;
  float far;
  float fov;

  float screen_width;
  float screen_height;

  public:
    camera(float near, float far, float fov);

    glm::mat4 view();
    glm::mat4 projection();

    void move_to(glm::vec3 pos);
    void look_at(glm::vec3 target);

    glm::vec3 position();

    void set_screen_dimensions(float sw, float sh);
    glm::vec3 billboard_normal();
};