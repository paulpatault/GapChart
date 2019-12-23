#version 330 core

uniform vec3 u_color;

in vec3 frag_Normal;
in vec3 frag_Position;

out vec4 color;


void main() {

    vec3 lightColor = vec3(1.f, 1.f, 1.f);

    vec3 lightPos = vec3(0.f, 0.f, 1000.f);
    vec3 viewPos = vec3(0.f, 0.f, 1000.f);

    vec3 position = frag_Position;

    //Ambient
    float ambientStrength = 0.7f; //0.1f;
    vec3 ambient = ambientStrength * lightColor;

    //Diffuse
    vec3 normal = normalize(frag_Normal);
    vec3 lightDir = normalize(lightPos - position);
    float diff = max(dot(normal, lightDir), 0.f);
    vec3 diffuse = diff * lightColor;

    vec3 result = (1) * u_color;

    color = vec4(result, 1.f);

}