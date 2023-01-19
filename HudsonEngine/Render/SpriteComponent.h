#pragma once
#include "../stdafx.h"

#include "Shader.h"
#include "Texture.h"
#include "../Entity/Component.h"

namespace Hudson::Render {

    class SpriteComponent : public Entity::Component
    {
    public:
        SpriteComponent();
        SpriteComponent(Shader* shader);
        SpriteComponent(Shader* shader, glm::vec2 gridSize, glm::vec2 gridPosition);
        ~SpriteComponent();

        void DrawSprite(Texture* texture, glm::vec2 position);
        void SetGridSize(glm::vec2 gridSize) { this->gridSize = gridSize; };
        glm::vec2 GetGridSize() { return this->gridSize; };

        void SetGridPos(glm::vec2 gridPos) { this->gridPos = gridPos; };
        glm::vec2 GetGridPos() { return this->gridPos; };

        void SetSize(glm::vec2 size) { this->size = size; };

        void SetColor(glm::vec3 color) { this->color = color; };

    private:
        Shader*       shader;
        unsigned int quadVAO;
        
        // Sprite Variables
        glm::vec2 gridSize = glm::vec2(1);
        glm::vec2 gridPos = glm::vec2(0);
        glm::vec3 color = glm::vec3(1);
        glm::vec2 size = glm::vec2(1);

        void initRenderData();

    };
}
