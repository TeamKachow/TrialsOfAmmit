#include "SpriteRenderer.h"

Hudson::Render::SpriteRenderer::SpriteRenderer(Shader* shader)
{
    this->shader = shader;
    this->initRenderData();


}

Hudson::Render::SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void Hudson::Render::SpriteRenderer::DrawSprite(Texture* texture, glm::vec2 position)
{
    this->shader->Use();
    glm::mat4 model = glm::mat4(1);

    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader->SetMatrix4("model", model);

    // render textured quad
    this->shader->SetVector3("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture->Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Hudson::Render::SpriteRenderer::SetSize(glm::vec2 size)
{
    this->size = size;
}

void Hudson::Render::SpriteRenderer::SetColor(glm::vec3 color)
{
    this->color = color;
}

void Hudson::Render::SpriteRenderer::initRenderData()
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

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
