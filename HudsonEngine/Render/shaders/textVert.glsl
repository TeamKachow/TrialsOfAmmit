#version 460 core
layout (location = 0) in vec4 vertex;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 model;

uniform float depth;

void main()
{
    gl_Position = projection * model * vec4(vertex.xy, depth, 1.0);
    TexCoords = vertex.zw;
}