#include "ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>

using namespace Hudson;

Common::ResourceManager* Common::ResourceManager::INSTANCE = nullptr;

Render::Shader* Common::ResourceManager::GetShader(std::string name)
{
	return &Shaders[name];
}

Render::Shader* Common::ResourceManager::LoadShader(const char* vertShaderFile, const char* fragShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vertShaderFile, fragShaderFile);
	return &Shaders[name];
}

Render::Texture* Common::ResourceManager::GetTexture(std::string name)
{
	return &Textures[name];
}

Render::Texture* Common::ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return &Textures[name];
}

void Common::ResourceManager::SetupInstance()
{
	INSTANCE = new Common::ResourceManager;
}

void Common::ResourceManager::Clear()
{
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

void Common::ResourceManager::DestroyInstance()
{
	INSTANCE->Clear();
	INSTANCE = nullptr;
}


Render::Shader Common::ResourceManager::loadShaderFromFile(const char* vertShaderFile, const char* fragShaderFile)
{
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
	// now create shader object from source code
	Render::Shader shader;
	shader.Compile(vertShaderCode, fragShaderCode);
	return shader;
};

Render::Texture Common::ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
	// create texture object
	Render::Texture texture;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // RGB compatible

	if (alpha) // Alpha should be true for PNG images and false for JPG
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // RGBA compatible
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
}