#pragma once
#include "../Util/stdafx.h"

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
        void SetGridSize(glm::vec2 gridSize) { this->_gridSize = gridSize; };
        glm::vec2 GetGridSize() { return this->_gridSize; };

        void SetGridPos(glm::vec2 gridPos) { this->_gridPos = gridPos; };
        glm::vec2 GetGridPos() { return this->_gridPos; };

        void SetSize(glm::vec2 size) { this->_size = size; };

        void SetColor(glm::vec3 color) { this->_color = color; };

    private:
        Shader*       _shader;
        unsigned int _quadVAO;
        
        // Sprite Variables
        glm::vec2 _gridSize = glm::vec2(1);
        glm::vec2 _gridPos = glm::vec2(0);
        glm::vec3 _color = glm::vec3(1);
        glm::vec2 _size = glm::vec2(1);

        void InitRenderData();

    };
}
