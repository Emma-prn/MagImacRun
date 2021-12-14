#ifndef __GRAPHICS_SHADER_HPP__
#define __GRAPHICS_SHADER_HPP__

#include <GL/glew.h>
#include <GL/gl.h>
#include <string_view>
#include <exception>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/*! \class shader_exception
 *  \brief Une exception lors de la création d'un shader.
 *
 *  Les exceptions nous permettent de faire rater des constructeurs. Un autre
 *  moyen de gérer les erreurs de constructions serait d'avoir une fonction
 *  "init" qui renvoie un code d'erreur si l'initialisation n'a pas réussi, mais
 *  avec une exception on permet de gérer les erreurs dès la construction et on
 *  empêche l'utilisateur de créer un objet et de ne pas l'initialiser ensuite
 *  (ça simplifie le code)
 */
class shader_exception : std::exception {
  public:
  enum type { VERT_SHDR_COMP, FRAG_SHDR_COMP, VERT_SHDR_FILE, FRAG_SHDR_FILE, PROG_LINK, VERT_SHDR_CREATE, FRAG_SHDR_CREATE, PROG_CREATE,
    UNKNOWN };

  shader_exception(type ty = UNKNOWN, GLuint object = 0);

  const char* what() const noexcept;
  std::string_view details() const noexcept;

  private:
  static const char *desc[];
  type ty;
  std::string detail;
};

/*! \class shader
 *  \brief Un programme GLSL (langage de shader d'OpenGL)
 *
 *  Cette classe encapsule la logique de création et manipulation des programmes
 *  OpenGL. Plutôt que de manipuler des indices (GLuint) d'objets OpenGL, on expose
 *  ainsi une classe qui permet de manipuler de manière contrôlée les objets
 *  OpenGL alloués et proprement initialisés.
 */
class shader {
  GLuint vertex;
  GLuint fragment;
  GLuint program;

  public:
    shader(const char *vertex_path, const char *fragment_path);
    ~shader();

    /*!
     *  \brief Active le shader
     *
     *  Le dernier shader ayant appelé la fonction use est celui qui sera
     *  utilisé pour les appels à glDraw*
     */
    void use() const;
    /*!
     *  \brief Récupère l'indice d'un attrib d'un shader
     *  \param name le nom de l'attribut
     *  \return l'indice de l'attribut
     */
    GLuint attrib_location(const char *name) const;

    /*!
     *
     *  \param name le nom de l'uniforme
     *  \param data la donnée à upload
     */
    /*! \{ */
    /*! \brief Upload un glm::vec3 */
    void set_vec3(const char *name, const glm::vec3& data) const;
    /*! \brief Upload un glm::mat4 */
    void set_mat4(const char *name, const glm::mat4& data) const;
    /*! \brief Upload un int */
    void set_int(const char *name, int data) const;
    /*! \} */
};

#endif // SHADER_HPP
