#version 300 es
precision mediump float;

in vec2 vFragText;

out vec3 FragColor;

uniform sampler2D tile;

void main(){
    vec4 text = texture(tile, vFragText);
    FragColor = vec3(text);
}