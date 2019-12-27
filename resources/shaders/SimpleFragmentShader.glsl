#version 330 core

uniform vec3 u_color;
uniform vec3 u_lightPos;

in vec3 frag_Position;
in vec3 frag_Normal;
in vec3 v_position;

out vec4 color;


void main() {

    vec3 lightColor = vec3(1.f, 1.f, 1.f);

    vec3 position = frag_Position;

    // Ambient
    float ambientStrength = 0.7f; // 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 normal = normalize(frag_Normal);
    vec3 lightDir = normalize(u_lightPos - position);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(v_position - position);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec *lightColor;


    vec3 result = (ambient + diffuse) * u_color;

    color = vec4(result, 1.f);

}