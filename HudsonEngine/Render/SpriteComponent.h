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

        void SetDepthOrder(float newZ) { this->zOrder = newZ; };
        float GetDepthOrder() { return this->zOrder; };

        // Offset relative to game object transform scale
        void SetXOffset(float xOff) { this->xOffset = xOff; };
        float GetXOffset() { return this->xOffset; };
        // Offset relative to game object transform scale
        void SetYOffset(float yOff) { this->yOffset = yOff; };
        float GetYOffset() { return this->yOffset; };

        void SetColor(glm::vec3 color) { this->_color = color; };
        glm::vec3 GetColor() { return this->_color; };

        Shader* GetShader() { return _shader; }

        void DrawPropertyUI() override;

    private:
        Shader*       _shader;
        Texture*      _texture;
        unsigned int  _quadVAO = UINT_MAX;
        
        // Sprite Variables
        float zOrder = 0;
        float xOffset = 0;
        float yOffset = 0;

        glm::vec2 _gridSize = glm::vec2(1);
        glm::vec2 _gridPos = glm::vec2(0);
        glm::vec3 _color = glm::vec3(1);
        glm::vec2 _size = glm::vec2(1);

        void InitRenderData();

    public:
        void FromJson(const nlohmann::json& j) override;
        void ToJson(nlohmann::json& j) override;
    };
}
