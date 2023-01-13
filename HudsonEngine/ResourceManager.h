
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>
#include <stb-master/stb_image.h>

#include "Shader.h"
#include "Texture.h"

namespace Hudson::Common {
	class ResourceManager
	{
		public:
			std::map<std::string, Render::Shader> Shaders;
			std::map<std::string, Render::Texture> Textures;

			// Shader
			Render::Shader GetShader(std::string name) {
				{
					return Shaders[name];
				}
			};
			Render::Shader LoadShader(const char* vertShaderFile, const char* fragShaderFile, std::string name)
			{
				Shaders[name] = loadShaderFromFile(vertShaderFile, fragShaderFile);
				return Shaders[name];
			};

			// Textures
			Render::Texture GetTexture(std::string name) {
				return Textures[name];
			}
			Render::Texture LoadTexture(const char* file, bool alpha, std::string name) {
				Textures[name] = loadTextureFromFile(file, alpha);
				return Textures[name];
			};

			// Memory Management
			static void Setup()
			{
				INSTANCE = new ResourceManager();
			}

			static void Destroy()
			{
				delete INSTANCE;
				INSTANCE = nullptr;
			}

			static ResourceManager* GetInstance()
			{
				return INSTANCE;
			}
			void Clear();

		private:
			static ResourceManager* INSTANCE;

			ResourceManager() {};
			// loads and generates a shader from file
			Render::Shader loadShaderFromFile(const char* vertShaderFile, const char* fragShaderFile) {
				std::string vertCode;
				std::string fragCode;

				try {
					std::stringstream vertShaderStream, fragShaderStream;

					std::ifstream vShaderFile(vertShaderFile);
					std::ifstream fShaderFile(fragShaderFile);
					// read file's buffer contents into streams
					vertShaderStream << vShaderFile.rdbuf();
					fragShaderStream << fShaderFile.rdbuf();
					// close file handlers
					vShaderFile.close();
					fShaderFile.close();
					// convert stream into string
					vertCode = vertShaderStream.str();
					fragCode = fragShaderStream.str();
				}
				catch (std::exception e)
				{
					std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
				}
				const char* vertShaderCode = vertCode.c_str();
				const char* fragShaderCode = fragCode.c_str();
				// 2. now create shader object from source code
				Render::Shader shader;
				shader.Compile(vertShaderCode, fragShaderCode);
				return shader;
			};

			// loads a single texture from file
			Render::Texture loadTextureFromFile(const char* file, bool alpha) {
				// create texture object
				Render::Texture texture;
				if (alpha)
				{
					texture.internalFormat = GL_RGBA;
					texture.imageFormat = GL_RGBA;
				}
				// load image
				int width, height, nrChannels;
				unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
				// now generate texture
				texture.Generate(width, height, data);
				// free image data
				stbi_image_free(data);
				return texture;
			};
	};
}

	

#endif

