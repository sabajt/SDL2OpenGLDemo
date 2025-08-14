#version 330 core

const int RT_PASSTHRU = 0;
const int RT_CIRCLE = 1;
const int RT_GRAD = 2;
const int RT_COOL = 3;

in mat4 fragModel;

uniform float screenHeight;
uniform int renderType;
uniform float alpha;
uniform vec3 color;
uniform float time;

out vec4 fragColor;

void renderPassthru() 
{
    fragColor = vec4(color.r, color.g, color.b, alpha);
}

void renderCircle()
{
    // (fragCoord - pos) / size
    float u = (gl_FragCoord.x - fragModel[3].x) / fragModel[0].x;
    float v = ((screenHeight - gl_FragCoord.y) - fragModel[3].y) / fragModel[1].y;
    
    vec2 p = vec2(u, v);
    vec2 center = vec2(0.5, 0.5);

    float distToCenter = length(p - center);
    
    if (distToCenter > 0.5) 
    {
        discard;
    }
    
    fragColor = vec4(color.r, color.g, color.b, alpha);
}

void renderGrad()
{
    float u = (gl_FragCoord.x - fragModel[3].x) / fragModel[0].x;
    float v = ((screenHeight - gl_FragCoord.y) - fragModel[3].y) / fragModel[1].y;
    
    vec2 p = vec2(u, v);
    vec2 center = vec2(0.5, 0.5);
    float d = length(p - center) * .01;
    
    fragColor = vec4(color.r * d, color.g * d, color.b * d, alpha);
}

void renderCool()
{
    float n = sin(time * 100.0)  + 1.0 / 2.0;
    float o = cos(time * 100.0)  + 1.0 / 2.0;

    float u = (gl_FragCoord.x - fragModel[3].x) / fragModel[0].x;
    float v = ((screenHeight - gl_FragCoord.y) - fragModel[3].y) / fragModel[1].y;
    
    
    vec2 p = vec2(u, v);
    vec2 center = vec2(n * 100.0, 0 * 100.0);
    float d = length(p - center) * .001;

    fragColor = vec4(color.r * d * u, color.g * d * v, color.b, alpha);
}

void main()
{
    switch (renderType)
    {
        case RT_PASSTHRU:
            renderPassthru();
            break;
            
        case RT_CIRCLE:
            renderCircle();
            break;
            
        case RT_GRAD:
            renderGrad();
            break;
            
        case RT_COOL:
            renderCool();
            break;
    }
}

