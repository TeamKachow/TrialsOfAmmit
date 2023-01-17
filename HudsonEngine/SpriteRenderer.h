#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"

namespace Hudson::Render {

    class SpriteRenderer
    {
    public:
        SpriteRenderer();
        SpriteRenderer(Shader* shader);
        ~SpriteRenderer();

        void DrawSprite(Texture* texture, glm::vec2 position);
        void SetSize(glm::vec2 size);
        void SetColor(glm::vec3 color);

    private:
        Shader*       shader;
        unsigned int quadVAO;
        
        // Sprite Variables
        glm::vec3 color = glm::vec3(1);
        glm::vec2 size = glm::vec2(1);

        void initRenderData();

    };
}

