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

vec3 pointLight(){

    vec3 lightVec = lightPos - camPos;
    float dist = length(lightVec);
    float a = 3.0;
    float b = 0.7;
    float inten = 1.f / (a*dist*dist+b*dist+1.f);

    float ambiant = 1.5f;

    vec3 norm = normalize(vNormale_vs);
    vec3 lightDir = normalize(lightVec);

    float diffuse = max(dot(norm,lightDir), 0.f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - vPosition_vs);
    vec3 reflection = reflect(-lightDir,norm);
    float specAmount = pow(max(dot(viewDirection,reflection),0.f), 8);
    float specular = specAmount * specularLight;
    vec4 text = texture(utexture,vTextCoords);

    return vec3(text) * lightColor * (diffuse * inten + ambiant + specular);

}

vec3 directLight(){

    float ambiant = 1.5f;

    vec3 norm = normalize(vNormale_vs);
    vec3 lightDir = normalize(vec3(1.f,1.f,0.f));

    float diffuse = max(dot(norm,lightDir), 0.f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - vPosition_vs);
    vec3 reflection = reflect(-lightDir,norm);
    float specAmount = pow(max(dot(viewDirection,reflection),0.f), 16);
    float specular = specAmount * specularLight;
    vec4 text = texture(utexture,vTextCoords);

    return vec3(text) * lightColor * (diffuse + ambiant + specular);
}

vec3 spotLight(){

    float outerCone = 0.5f;
    float innerCone = 0.55f;

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

    float angle = dot(vec3(0.f, -1.f, 0.f),-lightDir);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.f, 1.f);

    return vec3(text) * lightColor * (diffuse * inten + ambiant + specular * inten);
}

void main() {

    fFragColor = spotLight();
};