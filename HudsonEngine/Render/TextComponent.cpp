#include "TextComponent.h"
#include "../Common/ResourceManager.h"
#include "../Entity/GameObject.h"

extern const std::filesystem::path filePath;

Hudson::Render::TextComponent::TextComponent() : TextComponent("../DemoGame/Fonts/arial.ttf", nullptr)
{

}


Hudson::Render::TextComponent::TextComponent(const char* path, Hudson::Render::Shader* newShader) : Component("Text")
{
	shader = newShader;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Loads TTF file in
	StartFreeType(std::filesystem::path(filePath) / path);
	// Generates and Stores textures for each character
	StoreCharacters(std::filesystem::path(filePath) / path);
}

Hudson::Render::TextComponent::~TextComponent()
{
	FT_Done_Face(_face);
	FT_Done_FreeType(_ft);
}

void Hudson::Render::TextComponent::StartFreeType(const std::filesystem::path& path)
{
	if (FT_Init_FreeType(&_ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	int ret = FT_New_Face(_ft, path.string().c_str(), 0, &_face);

	if (ret)
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << ret << std::endl;
	}

}

void Hudson::Render::TextComponent::StoreCharacters(const std::filesystem::path& path)
{
	// This function goes through every character and stores them as textures.

	if (FT_New_Face(_ft, path.string().c_str(), 0, &_face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
	else
	{
		FT_Set_Pixel_Sizes(_face, 0, 32);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

		for (unsigned char c = 0; c < 128; c++)
		{
			// load character glyph 
			if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _face->glyph->bitmap.width, _face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, _face->glyph->bitmap.buffer);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {
				texture,
				glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
				glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
				static_cast<unsigned int>(_face->glyph->advance.x)
			};
			Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	FT_Done_Face(_face);
	FT_Done_FreeType(_ft);
}

void Hudson::Render::TextComponent::Draw(glm::vec2 position)
{
	// This function uses the texture to render text
	scale = _parent->GetTransform().scale.x;

	// activate corresponding render state	
	glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(position, 0.0f));
	shader->Use();

	shader->SetMatrix4("model", model);

	//glUniform3f(glGetUniformLocation(s.Program, "textColor"), color.x, color.y, color.z);
	shader->SetFloat3("textColor", color.x, color.y, color.z);
	shader->SetFloat("depth", zOrder);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// 50, 50
	// 2mill
	int originX = position.x;

	int newLineCount = 0;

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		if (*c != 0x0A) // Enter Key in Hex
		{
			Character ch = Characters[*c];

			float poX = position.x + ch.Bearing.x * scale;
			float poY = (position.y + (newLineCount * newLineOffset)) + (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;

			// update VBO for each character
			float vertices[6][4] = {
				{ poX,     poY - h,   0.0f, 0.0f },
				{ poX,     poY,       0.0f, 1.0f },
				{ poX + w, poY,       1.0f, 1.0f },

				{ poX,     poY - h,   0.0f, 0.0f },
				{ poX + w, poY,       1.0f, 1.0f },
				{ poX + w, poY - h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			position.x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
		}
		else
		{
			position.x = originX;
			++newLineCount;
		}
	}


	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Hudson::Render::TextComponent::DrawPropertyUI()
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	ImGui::InputTextMultiline("Content", &text);

	ImGui::DragFloat3("Color RGB", &color.x, 0.1f, 0.0f, 1.0f);
	ImGui::DragFloat("Line Spacing", &newLineOffset, 0.5);
	ImGui::DragFloat("Text Scale", &scale, 0.5);

	ImGui::Text("Current Font:");
	ImGui::SameLine();
	ImGui::TextDisabled("Place Font Here");
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* pl = ImGui::AcceptDragDropPayload("ContentItem"))
		{
			const wchar_t* path = (const wchar_t*)pl->Data;

			std::wcout << path << std::endl;

			_fontPath = converter.to_bytes(std::filesystem::relative(std::filesystem::path(filePath) / path));

			Characters.clear();

			StartFreeType(std::filesystem::path(filePath) / path);
			StoreCharacters(std::filesystem::path(filePath) / path);
		}
		ImGui::EndDragDropTarget();
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("Font path: %s", _fontPath.c_str());
	}
}

void Hudson::Render::TextComponent::FromJson(const nlohmann::json& j)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::string fontPath = j.at("fontPath");
	if (!fontPath.empty())
	{
		_fontPath = fontPath;
		StartFreeType(_fontPath);
		StoreCharacters(_fontPath);
	}

	text = j.at("text");
	scale = j.at("scale");
	color = j.at("color");
	newLineOffset = j.at("newLineOffset");
}

void Hudson::Render::TextComponent::ToJson(nlohmann::json& j)
{
	j["text"] = text;
	j["scale"] = scale;
	j["color"] = color;
	j["newLineOffset"] = newLineOffset;
	j["fontPath"] = _fontPath;
}
