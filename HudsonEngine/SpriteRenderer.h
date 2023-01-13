#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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


#endif

