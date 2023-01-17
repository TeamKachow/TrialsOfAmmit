#pragma once

#include <map>
#include <string>

#include <glad/glad.h>

#include "Shader.h"
#include "Texture.h"

namespace Hudson::Common {
	class ResourceManager
	{
		public:
			std::map<std::string, Render::Shader> Shaders;
			std::map<std::string, Render::Texture> Textures;
			// Shader
			Render::Shader* GetShader(std::string name);
			Render::Shader* LoadShader(const char* vertShaderFile, const char* fragShaderFile, std::string name);

			// Textures
			Render::Texture* GetTexture(std::string name);
			Render::Texture* LoadTexture(const char* file, bool alpha, std::string name);

			// Memory Management
			static ResourceManager* GetInstance() { return INSTANCE; };
			static void SetupInstance();
			static void DestroyInstance();
			void Clear();
		private:
			static ResourceManager* INSTANCE;

			ResourceManager() {};

			// loads and generates a shader from file
			Render::Shader loadShaderFromFile(const char* vertShaderFile, const char* fragShaderFile);

			// loads a single texture from file
			Render::Texture loadTextureFromFile(const char* file, bool alpha);
	};
}

