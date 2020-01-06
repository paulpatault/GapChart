#version 330 core

uniform vec3 u_color;
uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_CameraPos;

in vec3 frag_Position;
in vec3 frag_Normal;


out vec4 color;


void main() {

    vec3 lightColor = vec3(1.f, 1.f, 1.f);

    // Ambient light
    float ambientStrength = 0.4f;
    vec3 ambient = ambientStrength * u_lightColor;

    // Diffuse light
    vec3 normal = normalize(frag_Normal);
    vec3 lightDir = normalize(u_lightPos - frag_Position);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;

    // specular light
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_CameraPos - frag_Position);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * u_lightColor;


    vec3 result = (ambient + diffuse + specular) * u_color;

    color = vec4(result, 1.f);

}