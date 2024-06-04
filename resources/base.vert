#version 410 core

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = vertex.zw;
    // vec2 coords = vertex.xy;
    // if(coords.x > 1.0)
    //     coords.x = 0;
    gl_Position = projection * model * vec4(vertex.xy, 0.0f, 1.0);
}