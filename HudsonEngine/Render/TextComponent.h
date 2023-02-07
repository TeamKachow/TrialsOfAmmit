#pragma once

#include "../Entity/Component.h"
#include "../Util/stdafx.h"

#include "../Render/Shader.h"
#include "../Render/Texture.h"
#include "../Common/IEditable.h"

struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

namespace Hudson::Render
{
	class TextComponent : public Entity::Component, public Hudson::Common::IEditable
	{
	public:
		TextComponent();
		TextComponent(const char* path, glm::vec2 position);
		~TextComponent();

        void StartFreeType(const std::filesystem::path& path);
		void StoreCharacters(const std::filesystem::path& path);

		const char* GetCH(const wchar_t* wc);

		void Draw(glm::vec2 position);

		void SetText(std::string txt) { text = txt; }
		void SetDepthOrder(float depthOrder) { zOrder = depthOrder; }
		void SetColor(glm::vec3 col) { color = col; }

		Shader* GetShader() { return shader; }
		float GetDepthOrder() { return this->zOrder; };

		void DrawPropertyUI() override;
        void FromJson(const nlohmann::json& j) override;
        void ToJson(nlohmann::json& j) override;

    private:
		Render::Shader* shader;

		FT_Library _ft;
		FT_Face _face;
		std::string _fontPath = "";

		std::map<char, Character> Characters;

		unsigned int VAO;
		unsigned int VBO;
		// Some of this can be passed in via GameObject
		std::string text;
		float scale;
		glm::vec3 color;

		// TODO serialise this
		float zOrder = 0;

		float newLineOffset = 30.0f;
	};
}



