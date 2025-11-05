#version 330 core

layout (location = 0) in vec2 aPos;

uniform mat4 projection;
uniform vec2 position;

void main()
{
    vec3 worldPos = vec3(aPos, 0.0) + vec3(position, 0.0);
    gl_Position = projection * vec4(worldPos, 1.0);
}