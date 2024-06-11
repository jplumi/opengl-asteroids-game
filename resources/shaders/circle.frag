#version 410 core

in vec2 coords;

out vec4 FragColor;

uniform vec3 objectColor;
uniform float thickness;

void main()
{
    vec2 uv = coords * 2 -1;

    float smoothness = 0.005;

    float distance = 1-length(uv);
    float alpha = smoothstep(0.0, smoothness, distance);
    alpha *= smoothstep(thickness+smoothness, thickness, distance);

    FragColor = vec4(objectColor, alpha);
}