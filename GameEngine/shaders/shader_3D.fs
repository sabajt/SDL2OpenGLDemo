#version 330 core

in vec2 customTexCoord;

out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//    fragColor = mix(texture(texture1, customTexCoord), texture(texture2, customTexCoord), 0.5);
    
    // Animate repeat
    vec4 t1 = texture(texture1, customTexCoord);
    vec4 t2 = texture(texture2, vec2(customTexCoord.x * 5, customTexCoord.y * 5));
    fragColor = max(t1, t2);
}
