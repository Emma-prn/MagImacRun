#version 330 core

in vec3 vPosition_vs;
in vec3 vNormale_vs;
in vec2 vTextCoords;

out vec3 fFragColor;

uniform sampler2D utexture;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec3 light(){
   
    float ambiant = 1.5f;

    vec3 norm = normalize(vNormale_vs);
    vec3 lightDir = normalize(lightPos - camPos);

    float diffuse = max(dot(norm,lightDir), 0.f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - vPosition_vs);
    vec3 reflection = reflect(-lightDir,norm);
    float specAmount = pow(max(dot(viewDirection,reflection),0.f), 16);
    float specular = specAmount * specularLight;
    vec4 text = texture(utexture,vTextCoords);

    return vec3(text) * lightColor * (diffuse + ambiant);
}

void main() {

    fFragColor = light();
};