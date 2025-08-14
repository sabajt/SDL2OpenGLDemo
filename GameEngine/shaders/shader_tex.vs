#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 customColor; // output a color to the fragment shader
out vec2 customTexCoord;

uniform vec2 offset;
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position + offset, 0.0, 1.0);
    customColor = color;
    customTexCoord = texCoord;
}
