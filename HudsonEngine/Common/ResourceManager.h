#pragma once
#include "../Util/stdafx.h"

#include "../Render/Shader.h"
#include "../Render/Texture.h"

namespace Hudson::Common {
	class ResourceManager
	{
		public:
			std::map<std::string, Render::Shader> _shaders;
			std::map<std::string, Render::Texture> _textures;
			// Shader
			Render::Shader* GetShader(std::string name);
			Render::Shader* LoadShader(const char* vertShaderFile, const char* fragShaderFile, std::string name);
			Render::Shader* LoadShaderLiteral(const char* vertShaderCode, const char* fragShaderCode, std::string name);

			// _textures
			Render::Texture* GetTexture(std::string name);
			Render::Texture* LoadTexture(const char* file, bool alpha, std::string name);
			Render::Texture* LoadTexture(std::filesystem::path file, bool alpha, std::string name);

			// Memory Management
			static ResourceManager* GetInstance() { return INSTANCE; };
			static void SetupInstance();
			static void DestroyInstance();
			void Clear();
		private:
			static ResourceManager* INSTANCE;

			ResourceManager() {};

			// loads and generates a _shader from file
			Render::Shader LoadShaderFromFile(const char* vertShaderFile, const char* fragShaderFile);
			Render::Shader LoadShaderFromLiteral(const char* vertCode, const char* fragCode);

			// loads a single texture from file
			Render::Texture LoadTextureFromFile(const char* file);
			Render::Texture LoadTextureFromFile(std::filesystem::path file);
	};
}
