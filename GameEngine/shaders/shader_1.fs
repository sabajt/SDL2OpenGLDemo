#version 330 core

in vec3 customColor;
in vec2 customPosition;
out vec4 outColor;

void main()
{
    outColor = vec4(customColor, 1.0);
//    outColor = vec4(customPosition, 0.2, 0.0);
}
