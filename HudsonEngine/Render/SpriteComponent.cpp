#include "../Render/SpriteComponent.h"

#include "../Entity/GameObject.h"

#include "../Common/ResourceManager.h"

extern const std::filesystem::path filePath;

Hudson::Render::SpriteComponent::SpriteComponent() : Component("Sprite")
{
}

Hudson::Render::SpriteComponent::SpriteComponent(Shader* shader, Texture* texture) : Component("Sprite")
{
    this->_shader = shader;
    this->_texture = texture;
    this->InitRenderData();
}

Hudson::Render::SpriteComponent::SpriteComponent(Shader* shader, Texture* texture, glm::vec2 gridSize, glm::vec2 gridPosition) : Component("Sprite"), _shader(shader), _texture(texture), _gridSize(gridSize), _gridPos(gridPosition)
{
    this->InitRenderData(); // Initializes quad

}

Hudson::Render::SpriteComponent::~SpriteComponent()
{
    glDeleteVertexArrays(1, &this->_quadVAO);
}

void Hudson::Render::SpriteComponent::DrawSprite(glm::vec2 position)
{
    // If these aren't set, don't draw
    if (!_texture || !_shader || _quadVAO >= UINT_MAX)
        return;

    _shader->Use();
    glm::mat4 model = glm::mat4(1);

    _size = _parent->GetTransform().scale;

    model = glm::translate(model, glm::vec3(position, 0.0f));
    // TODO: make sprite's _size a multiplier of transform's _size
    model = glm::translate(model, glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.0f));
    model = glm::scale(model, glm::vec3(_size, 1.0f));

    _shader->SetMatrix4("model", model);

    // render textured quad
    _shader->SetVector3("spriteColor", _color);

    _shader->SetVector2("gridPos", _gridPos);
    _shader->SetVector2("gridSize", _gridSize);

    // GL_TEXTURE0 is the index of how many Textures are bound to one Texture ID
    // We should only ever expect to start at 0 index so GL_TEXTURE0 is fine
    // https://www.khronos.org/opengl/wiki/Texture - The glActiveTexture function defines the texture image unit that any function that takes a texture target as a parameter uses. - 
    glActiveTexture(GL_TEXTURE0);
    _texture->Bind();

    glBindVertexArray(this->_quadVAO);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void Hudson::Render::SpriteComponent::DrawPropertyUI()
{
    ImGui::InputFloat2("Grid Size", &_gridSize.r);
    ImGui::InputFloat2("Grid Position", &_gridPos.r);
    ImGui::ColorEdit3("Colour Tint", &_color.r);
    ImGui::InputFloat2("Size", &_size.r); 

    ImGui::Text("Texture: ");
    ImGui::SameLine();
    ImGui::TextDisabled("Place Here");

    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* pl = ImGui::AcceptDragDropPayload("ContentItem"))
        {
            const wchar_t* path = (const wchar_t*)pl->Data;

            std::wcout << path << std::endl;

            _texture = nullptr;

            static Hudson::Common::ResourceManager* resMan = Hudson::Common::ResourceManager::GetInstance();

            std::filesystem::path fullPath = filePath / path;
            resMan->LoadTexture(fullPath, true, fullPath.string());
            _texture = resMan->GetTexture(fullPath.string());
        }
        ImGui::EndDragDropTarget();
    }
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

void Hudson::Render::SpriteComponent::FromJson(const nlohmann::json& j)
{
    // TODO: _shader = resourceManager->GetShaderName(j.at("shader"));
    // TODO: _texture = resourceManager->GetTextureName(j.at("texture"));

    _gridSize = j.at("gridSize");
    _gridPos = j.at("gridPos");
    _color = j.at("color");
    _size = j.at("size");
}

void Hudson::Render::SpriteComponent::ToJson(nlohmann::json& j)
{
    // TODO: j["shader"] = resourceManager->GetShaderName(_shader);
    // TODO: j["texture"] = resourceManager->GetTextureName(_texture);

    j["gridSize"] = _gridSize;
    j["gridPos"] = _gridPos;
    j["color"] = _color;
    j["size"] = _size;
}
