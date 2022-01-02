#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormale;
layout(location = 2) in vec2 aVertexTextCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs;
out vec3 vNormale_vs;
out vec2 vTextCoords;

void main() {
  vec4 vertexPosition = vec4(aVertexPosition, 1);
  vec4 vertexNormale = vec4(aVertexNormale, 0);

  vPosition_vs = vec3(uMVMatrix * vertexPosition);
  vNormale_vs = vec3(uNormalMatrix * vertexNormale);
  vTextCoords = aVertexTextCoords;
  
  gl_Position = uMVPMatrix * vertexPosition;
};