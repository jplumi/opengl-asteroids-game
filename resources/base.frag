#version 410 core

in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 objectColor;
uniform sampler2D image;

void main()
{
    FragColor = vec4(objectColor, 1.0) * texture(image, TexCoords);
}