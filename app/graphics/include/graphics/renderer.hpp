/*#pragma once

#include <graphics/shader.hpp>
#include <graphics/model.hpp>
#include <geometry/spatial_object.hpp>

#include <memory>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <map>

/*! \class mesh_id
 *  \brief mesh index dans un renderer
 *
 *  La seule façon de dessiner un maillage est d'utiliser ces id. Comme leur seul
 * constructeur public est l'id "null mesh", nous pouvons l'utiliser pour montrer encore
 * quelque chose si quelqu'un a un mauvais mesh id. La seule façon de ne pas avoir un maillage nul
 * est d'utiliser les identifiants renvoyés par \ref renderer::register_mesh et ses variantes.
 */
class mesh_id {
  size_t i = 0;
  // Le membre de la classe doit être accédé par ces 2 objets, ils vont
  // être amis. -> ok car ils font partie du même module.
  friend class renderer;
  friend bool operator<(const mesh_id i1, const mesh_id i2);
};

//! en public ce n'est pas suffisant pour std::map 
//! donc operateur std::less de mesh_id mais pas dans la classe
inline bool operator<(const mesh_id i1, const mesh_id i2) {
  return i1.i < i2.i;
}

/*! \class renderer
 *  \brief Classe qui dessine des choses dans la scene 3D
 *
 *  Cette classe gère entièrement la mémoire dédiée au calcul graphique, et les
 *  appels OpenGL pour afficher des objets.
 */
class renderer {
  public:
    renderer(std::shared_ptr<shader> shd);

    /*! \name Fonctions d'enregistrement de mesh (maillages de points)
     *  
     *  Ces fonctions permettent d'enregistrer des mesh et de les
     *  référencer
     *  \{
     */
    /*! Enregistre un mesh à partir de ses points. A n'utiliser que si on
     * reçoit les données sous ce format avec impossibilité de le transformer
     * en une forme plus optimisée.
     *
     * Si on peut accéder à une version indexée, il vaut mieux l'utiliser.
     */
    mesh_id register_mesh(const std::vector<vertex>&, const std::string& texture_path);
    /*! Enregistre un mesh avec des points indexés (les coordonnées d'un point
     *  peuvent être référencées plusieurs fois).
     */
    mesh_id register_mesh(const std::vector<vertex>&, const std::vector<GLuint>&, const std::string& texture_path);
    /*! Enregistre un mesh défini par un fichier de type .obj */
    mesh_id register_mesh_from_obj(const std::string& filepath);
    /*! \} */

    /*! \name Fonctions d'affichage
     * 
     *  Ces fonctions servent à ajouter une commande de dessin. Elles ne
     *  dessinent pas elles même, mais préparent la scène. Pour générer le rendu
     *  final, utilisez la fonction \ref renderer::render
     *
     *  \{
     */
    /*! \brief Affiche un mesh à une certaine position, avec une certaine couleur */
    void draw(mesh_id mesh, glm::vec3 position, glm::vec3 color = glm::vec3(1));
    /*! \brief Affiche un mesh à une certaine position, à une certaine échelle, avec une certaine couleur */
    void draw_scaled(mesh_id mesh, glm::vec3 position, glm::vec3 scale, glm::vec3 color = glm::vec3(1));
    /*! \brief Affiche un mesh avec une certaine transformation, avec une certaine couleur */
    void draw_transformed(mesh_id mesh, glm::mat4 transform, glm::vec3 color = glm::vec3(1));
    /*! \brief Version par tableau de la fonction \ref renderer::draw */
    void draw(mesh_id mesh, const std::vector<glm::vec3>& positions, glm::vec3 color = glm::vec3(1));
    /*! \} */

    /*! \brief Exécute toutes les commandes de dessin enregistrées par la
     *  foctions \ref renderer::draw et ses variantes.
     */
    void render();
  private:
    
    struct model_instance {
      model the_model;
      std::vector<draw_instance> instances;
    };

    size_t next_free_mesh_id = 1;

    std::shared_ptr<shader> shd;

    std::shared_ptr<SDL_Window> window;
    std::map<mesh_id, model_instance> model_instances;
    std::map<std::string, mesh_id> model_by_name;
};*/