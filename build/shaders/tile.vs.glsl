#version 300 es

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aVertexTexture;

out vec2 vFragText;

uniform mat4 matPos;
uniform mat4 projection;
uniform mat4 view;

void main() {
  vFragText = aVertexTexture;
  vec4 transformed = projection * view * matPos * vec4(aPos.x, 0, aPos.y, 1);
  gl_Position = transformed;
};