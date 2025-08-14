#version 330 core

in vec3 customColor;
in vec2 customTexCoord;

out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float repeatScale;
uniform float blendValue;

void main()
{
    // Normal:
    //fragColor = texture(tex, customTexCoord)
    
    // Color:
    //fragColor = texture(texture1, customTexCoord) * vec4(customColor, 0);
    
    // Blend:
    //fragColor = mix(texture(texture1, customTexCoord), texture(texture2, customTexCoord), 0.5);
    
    // Ex 1 - flip one tex horizontal
    // https://learnopengl.com/Getting-started/Textures
    //vec4 t1 = texture(texture1, customTexCoord);
    // Negating instead of inverting values works too only if rendering mode is GL_REPEAT
    //vec4 t2 = texture(texture2, vec2(-customTexCoord.x, customTexCoord.y));
    //vec4 t2 = texture(texture2, vec2(1.0 - customTexCoord.x, customTexCoord.y));
    //fragColor = mix(t1, t2, 0.5);
    
    // Ex 2 - different ranges
    //vec4 t1 = texture(texture1, customTexCoord);
    //vec4 t2 = texture(texture2, vec2(customTexCoord.x * 2.0, customTexCoord.y * 2.0));
    //fragColor = mix(t1, t2, 0.5);
    
    // Animate repeat
    vec4 t1 = texture(texture1, customTexCoord);
    vec4 t2 = texture(texture2, vec2(customTexCoord.x * repeatScale, customTexCoord.y * repeatScale));
    fragColor = mix(t1, t2, blendValue);
}
