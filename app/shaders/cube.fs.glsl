#version 300 es
precision mediump float;

out vec3 FragColor;

in vec3 vFragText;

uniform samplerCube cube;

void main(){
    FragColor = vec3(texture(cube,vFragText));
}