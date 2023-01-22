#include "SpriteComponent.h"

#include "../Entity/GameObject.h"

Hudson::Render::SpriteComponent::SpriteComponent(Shader* shader)
{
    this->_shader = shader;
    this->InitRenderData();
}

Hudson::Render::SpriteComponent::SpriteComponent(Shader* shader, glm::vec2 gridSize, glm::vec2 gridPosition)
{

}

Hudson::Render::SpriteComponent::~SpriteComponent()
{
    glDeleteVertexArrays(1, &this->_quadVAO);
}

void Hudson::Render::SpriteComponent::DrawSprite(Texture* texture, glm::vec2 position)
{
    this->_shader->Use();
    glm::mat4 model = glm::mat4(1);

    _size = _parent->GetTransform().scale;

    model = glm::translate(model, glm::vec3(position, 0.0f));
    // TODO: make sprite's _size a multiplier of transform's _size
    model = glm::translate(model, glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f));
    model = glm::scale(model, glm::vec3(_size, 1.0f));

    this->_shader->SetMatrix4("model", model);

    // render textured quad
    this->_shader->SetVector3("spriteColor", _color);

    this->_shader->SetVector2("_gridPos", _gridPos);
    this->_shader->SetVector2("_gridSize", _gridSize);

    // GL_TEXTURE0 is the index of how many Textures are bound to one Texture ID
    // We should only ever expect to start at 0 index so GL_TEXTURE0 is fine
    // https://www.khronos.org/opengl/wiki/Texture - The glActiveTexture function defines the texture image unit that any function that takes a texture target as a parameter uses. - 
    glActiveTexture(GL_TEXTURE0);
    texture->Bind();

    glBindVertexArray(this->_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Hudson::Render::SpriteComponent::InitRenderData()
{
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->_quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->_quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
