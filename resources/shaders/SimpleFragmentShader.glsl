#version 330 core

uniform vec4 u_color;

in vec4 mycolor;
in vec3 frag_Normal;
in vec3 frag_Position;

out vec4 color;


void main(){

    color = mycolor;

    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    vec3 lightPos = vec3(0.0, .0, 1000.f);
    vec3 viewPos = vec3(0.0, .0, 1000.f);


    vec3 position = frag_Position;

    //Ambient
    float ambientStrength = 0.5f;
    vec3 ambient = ambientStrength * lightColor;

    //Diffuse
    vec3 normal = normalize(frag_Normal);
    vec3 lightDir = normalize(lightPos - position);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient) * vec3(u_color);

    color = vec4(result, 1.f);

}