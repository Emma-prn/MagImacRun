#version 330 core
out vec3 FragColor;

in vec3 vFragText;

uniform samplerCube cube;

void main(){
    FragColor = vec3(texture(cube,vFragText));
}