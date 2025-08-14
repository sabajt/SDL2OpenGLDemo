#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;

out vec3 customColor; // output a color to the fragment shader
out vec2 customPosition;

uniform vec2 offset;

void main()
{
    gl_Position = vec4(position + offset, 0.0, 1.0);
    // upside down:
    //gl_Position = vec4(position.x, -position.y, 0.0, 1.0);
    customColor = color;
    customPosition = position;
}
