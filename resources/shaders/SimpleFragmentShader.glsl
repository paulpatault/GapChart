#version 330 core

// add
smooth in float frag_Depth;
in vec3 frag_Position;
// end

in vec4 mycolor;

out vec4 color;


float near = 0.1;
float far  = 100.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main(){
    color = mycolor;
    vec3 position = frag_Position;

    float depth = LinearizeDepth(frag_Depth) / far; // divide by far for demonstration
    //color = vec4(vec3(depth), 1.0);
    //color /= 2;

}