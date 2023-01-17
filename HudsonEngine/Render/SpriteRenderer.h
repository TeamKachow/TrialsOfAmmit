#pragma once
#include "../stdafx.h"

#include "Shader.h"
#include "Texture.h"

namespace Hudson::Render {

    class SpriteRenderer
    {
    public:
        SpriteRenderer(Shader& shader);
        ~SpriteRenderer();

        void DrawSprite(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);
    private:
        Shader       shader;
        unsigned int quadVAO;

        void initRenderData();

    };
}
