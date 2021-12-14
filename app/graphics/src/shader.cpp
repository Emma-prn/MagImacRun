#include <graphics/shader.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

const char *shader_exception::desc[] = {
    "Could not compile vertex shader",
    "Could not compile fragmens Shader",
    "Error while opening/reading vertex shader file",
    "Error while opening/reading fragment shader file",
    "Error while linking the program",
    "Could not allocate the vertex shader",
    "Could not allocate the fragment shader",
    "Could not allocate the program",
    "Unknown shader error"
};

shader_exception::shader_exception(type ty, GLuint object) : ty(ty) {
  std::vector<GLchar> buffer;
  GLsizei len;
  switch (ty) {
    case VERT_SHDR_COMP:
    case FRAG_SHDR_COMP:
      glGetShaderiv(object, GL_INFO_LOG_LENGTH, &len);
      buffer.resize(len);
      glGetShaderInfoLog(object, len, &len, buffer.data());
      break;
    case PROG_LINK:
      glGetProgramiv(object, GL_INFO_LOG_LENGTH, &len);
      buffer.resize(len);
      glGetProgramInfoLog(object, len, &len, buffer.data());
      break;
    default: len = 0; break;
  }
  this->detail = std::string(buffer.begin(), buffer.begin() + len);
}

const char* shader_exception::what() const noexcept {
  return desc[ty];
}

std::string_view shader_exception::details() const noexcept {
  return std::string_view(detail);
}

shader::shader(const char *vertex_path, const char *fragment_path) {

  // throw s'il y a une erreur
  shader_exception except;

  // source buffer
  std::ostringstream oss;
  std::string scontent;
  const char *content;

  // opengl status variable
  GLint status;

  // shader files
  std::ifstream vertex_file, fragment_file;

  vertex = 0;
  fragment = 0;
  program = 0;

  // Allocate shaders
  vertex = glCreateShader(GL_VERTEX_SHADER);
  if (!vertex) {
    except = shader_exception(shader_exception::VERT_SHDR_CREATE);
    goto cleanup;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  if (!fragment) {
    except = shader_exception(shader_exception::FRAG_SHDR_CREATE);
    goto cleanup;
  }

  // Compile shaders

  // open vertex shader
  vertex_file.open(vertex_path);
  if (!vertex_file) {
    except = shader_exception(shader_exception::VERT_SHDR_FILE);
    goto cleanup;
  }

  // lit le vertex shader
  oss << vertex_file.rdbuf();

  // recupère son contenu
  scontent = oss.str();
  content = scontent.c_str();

  // bind source au shader opengl
  glShaderSource(vertex, 1, &content, nullptr);

  // compile vertex shader
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    except = shader_exception(shader_exception::VERT_SHDR_COMP, vertex);
    goto cleanup;
  }


  // reset oss et recommencer pour le fragment shader
  oss.str("");
  oss.clear();

  fragment_file.open(fragment_path);
  if (!fragment_file) {
    except = shader_exception(shader_exception::FRAG_SHDR_FILE);
    goto cleanup;
  }

  // lit le fragment shader
  oss << fragment_file.rdbuf();

  // récupère son contenu
  scontent = oss.str();
  content = scontent.c_str();

  // bind source au shader opengl
  glShaderSource(fragment, 1, &content, nullptr);

  // compile vertex shader
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    except = shader_exception(shader_exception::FRAG_SHDR_COMP, fragment);
    goto cleanup;
  }

  // Allocate program
  program = glCreateProgram();
  if (!program) {
    except = shader_exception(shader_exception::PROG_CREATE);
    goto cleanup;
  }

  // Attach shaders
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  // Link program
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    except = shader_exception(shader_exception::PROG_LINK, program);
    goto cleanup;
  }

  // nettoyer avant de renvoyer
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return;

  // nettoyer avant de lancer l'exception
  cleanup:
    if (vertex) { glDeleteShader(vertex); }
    if (fragment) { glDeleteShader(fragment); }
    if (program) { glDeleteProgram(program); }
    throw except;
}

shader::~shader() {
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  glDeleteProgram(program);
}

void shader::use() const {
  glUseProgram(program);
}

GLuint shader::attrib_location(const char *name) const {
  return glGetAttribLocation(program, name);
}

void shader::set_vec3(const char *name, const glm::vec3& data) const {
  GLuint loc = glGetUniformLocation(program, name);
  glUniform3fv(loc, 1, glm::value_ptr(data));
}

void shader::set_mat4(const char *name, const glm::mat4& data) const {
  GLuint loc = glGetUniformLocation(program, name);
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data));
}

void shader::set_int(const char *name, int data) const {
  GLuint loc = glGetUniformLocation(program, name);
  glUniform1i(loc, data);
}
