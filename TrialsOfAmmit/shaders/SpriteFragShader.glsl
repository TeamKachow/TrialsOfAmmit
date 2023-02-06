#version 460 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D sampler;
uniform vec3 spriteColor;

void main()
{   
    vec4 tempColor = vec4(spriteColor, 1.0) * texture(sampler, TexCoords);
    if(tempColor.a < 0.1)
        discard;

    color = tempColor;
} 