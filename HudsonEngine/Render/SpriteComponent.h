#pragma once
#include "../Util/stdafx.h"

#include "../Render/Shader.h"
#include "../Render/Texture.h"
#include "../Entity/Component.h"
#include "../Common/IEditable.h"

namespace Hudson::Render {

    class SpriteComponent : public Entity::Component, public Common::IEditable
    {
    public:
        SpriteComponent();
        SpriteComponent(Shader* shader, Texture* texture);
        SpriteComponent(Shader* shader, Texture* texture, glm::vec2 gridSize, glm::vec2 gridPosition);
        SpriteComponent(const SpriteComponent& other) = default;
        ~SpriteComponent();

        void DrawSprite(glm::vec2 position);
        void SetGridSize(glm::vec2 gridSize) { this->_gridSize = gridSize; };
        glm::vec2 GetGridSize() { return this->_gridSize; };

        void SetGridPos(glm::vec2 gridPos) { this->_gridPos = gridPos; };
        glm::vec2 GetGridPos() { return this->_gridPos; };

        void SetSize(glm::vec2 size) { this->_size = size; };
        void SetColor(glm::vec3 color) { this->_color = color; };

        Shader* GetShader() { return _shader; }

        void DrawPropertyUI() override;

    private:
        Shader*       _shader;
        Texture*      _texture;
        unsigned int  _quadVAO = UINT_MAX;
        
        // Sprite Variables
        glm::vec2 _gridSize = glm::vec2(1);
        glm::vec2 _gridPos = glm::vec2(0);
        glm::vec3 _color = glm::vec3(1);
        glm::vec2 _size = glm::vec2(1);

        void InitRenderData();

    };
}
