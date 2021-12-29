#version 330 core

layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec2 aVertexTexture;

out vec3 vFragText;

uniform mat4 matPos;
uniform mat4 projection;
uniform mat4 view;

void main() {
  vFragText = vec3(aPos.x, aPos.y, aPos.z);
  vec4 transformed = projection * view * matPos * vec4(aPos, 1);
  gl_Position = transformed;
};