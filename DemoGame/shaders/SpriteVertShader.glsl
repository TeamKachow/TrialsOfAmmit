#version 460 core
layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform vec2 gridPos;
uniform vec2 gridSize;

void main()
{   
    vec2 position = vertex.xy;
    vec2 texCoords = vertex.zw;

    float xWidth = 1.0 / gridSize.x;
    float yHeight = 1.0 / gridSize.y;

    float texX = gridPos.x * xWidth;
    float texY = gridPos.y * yHeight;

    texCoords.x = texX + (texCoords.x * xWidth);
    texCoords.y = texY + (texCoords.y * yHeight);

    TexCoords = texCoords;

    gl_Position = projection * model * vec4(position, 0.0, 1.0);
}