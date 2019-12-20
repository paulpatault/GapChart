#version 330 core

layout(location = 0) in vec4 position;
layout( location = 1 ) in vec3 normal;


out vec4 mycolor;
out vec3 frag_Normal;

// add
out vec3 frag_Position;
out float frag_Depth;
// end

uniform vec4 u_color;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

float scalar = position.z / 20;

void main(){

    gl_Position = u_Projection * u_View * u_Model * position;
/*
    frag_Normal = mat3(transpose(inverse(u_Model))) * in_Normal;

    ////COLOR
    vec3 c_position = frag_Position;

    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    //Diffuse
    vec3 normal = normalize(frag_Normal);
    vec3 lightDir = normalize(vec3(0.0, .0, 1000.f) - c_position); // remplacement := u_LightPos = vec3(0.0)
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - position);    /// u_ViewPos = vec3(0)
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * vec3(mycolor);


    vec3 result = (ambient + diffuse) * vec3(u_color);
    mycolor = u_color; //vec4(result, 1.f);
*/

    //// END

    if(position.z < 0.15){
//        mycolor = vec4(vec3(u_color*scalar), 1.f) ;
        mycolor = u_color;
    }
    else{
        mycolor = u_color;
    }


    // add
    frag_Position = vec3(u_Projection * u_View * u_Model * position);
    frag_Depth = gl_Position.z;
    // end

}