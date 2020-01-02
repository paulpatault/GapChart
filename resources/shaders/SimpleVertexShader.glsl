#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

uniform mat4 u_Model;
uniform mat4 u_Rotate;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 frag_Normal;
out vec3 frag_Position;

void main()
{
    gl_Position = u_Projection * u_View * u_Rotate * u_Model * vec4(in_Position, 1.f);

    frag_Position = vec3(u_Rotate * u_Model * vec4(in_Position, 1.f));
    frag_Normal = mat3(transpose(inverse(u_Rotate * u_Model))) * in_Normal;
}
