#version 330 core

layout (location = 0) in vec2 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 uColor;

out vec3 fragColor;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
    fragColor = uColor;
}