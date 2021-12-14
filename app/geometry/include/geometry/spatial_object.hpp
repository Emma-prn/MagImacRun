#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

/*! \interface spatial_object
 *  \brief représente un objet ayant une position, rotation, et échelle dans un
 *  espace 3D.
 */
class spatial_object {
  glm::mat4 m_transform;
  public:
    spatial_object(glm::mat4 transform = glm::mat4());

    virtual glm::mat4 global_transform() const;
    const glm::mat4& local_transform() const;

    void move_to(glm::vec3);
    void translate(glm::vec3);
    void translate_xz(glm::vec2);
    void rotate(glm::vec3, float);

    void set_transform(glm::mat4);
};