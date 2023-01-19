#version 460 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform vec2 gridPos; // vec2(2,3); // This is 0 index
uniform vec2 gridSize; // vec2(3,4); // This is 1 index

void main()
{   
    vec2 position = vertex.xy;
    vec2 texCoords = vertex.zw;

    // X size
    float xWidth = 1.0 / gridSize.x; // 0.33
    // Y size
    float yHeight = 1.0 / gridSize.y; // 0.25

    float texX = gridPos.x * xWidth;
    float texY = gridPos.y * yHeight;

    texCoords.x = texX + (texCoords.x * xWidth);
    texCoords.y = texY + (texCoords.y * yHeight);

    TexCoords = texCoords;

    gl_Position = projection * model * vec4(position, 0.0, 1.0);
}