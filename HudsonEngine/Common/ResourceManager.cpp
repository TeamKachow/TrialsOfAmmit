#include "ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>

using namespace Hudson;

Common::ResourceManager* Common::ResourceManager::INSTANCE = nullptr;

Render::Shader* Hudson::Common::ResourceManager::PreFetchShader(std::string name)
{
	return &_shaders[name];
}

Render::Shader* Common::ResourceManager::GetShader(std::string name)
{
	if (_shaders.find(name) != _shaders.end()) {
		return &_shaders[name];
	}
	else {
		return nullptr;
	}
}

Render::Shader* Common::ResourceManager::LoadShader(const char* vertShaderFile, const char* fragShaderFile, std::string name)
{
	_shaders[name] = LoadShaderFromFile(vertShaderFile, fragShaderFile);
	return &_shaders[name];
}

Render::Shader* Hudson::Common::ResourceManager::LoadShaderLiteral(const char* vertShaderCode, const char* fragShaderCode, std::string name)
{
	_shaders[name] = LoadShaderFromLiteral(vertShaderCode, fragShaderCode);
	return &_shaders[name];
}

std::string Common::ResourceManager::GetShaderName(Render::Shader* shader)
{
	if (shader == nullptr)
	{
		return "";
	}

	for (auto&& [name, value] : _shaders)
	{
		if (shader->ID == value.ID)
			return name;
	}

	return "";
}

Render::Texture* Common::ResourceManager::GetTexture(std::string name)
{
	if (_textures.find(name) != _textures.end()) {
		return &_textures[name];
	}
	else {
		return nullptr;
	}
}

std::string Common::ResourceManager::GetTextureName(Render::Texture* texture)
{
	if (texture == nullptr)
	{
		return "";
	}

    for (auto && [name, tex]: _textures)
    {
		if (texture->ID == tex.ID)
			return name;
    }

	return "";
}

Render::Texture* Common::ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
	_textures[name] = LoadTextureFromFile(file);
	return &_textures[name];
}

Render::Texture* Common::ResourceManager::LoadTexture(std::filesystem::path file, bool alpha, std::string name)
{
	_textures[name] = LoadTextureFromFile(file);
	return &_textures[name];
}

void Common::ResourceManager::SetupInstance()
{
	INSTANCE = new Common::ResourceManager;
}

void Common::ResourceManager::Clear()
{
    for (auto iter : _shaders)
        glDeleteProgram(iter.second.ID);
    for (auto iter : _textures)
        glDeleteTextures(1, &iter.second.ID);
}

void Common::ResourceManager::DestroyInstance()
{
	INSTANCE->Clear();
	INSTANCE = nullptr;
}


Render::Shader Common::ResourceManager::LoadShaderFromFile(const char* vertShaderFile, const char* fragShaderFile)
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
		std::cout << "Failed to read shader files" << std::endl;
	}
	const char* vertShaderCode = vertCode.c_str();
	const char* fragShaderCode = fragCode.c_str();
	// now create shader object from source code
	Render::Shader shader;
	shader.Compile(vertShaderCode, fragShaderCode);
	return shader;
}

Render::Shader Hudson::Common::ResourceManager::LoadShaderFromLiteral(const char* vertCode, const char* fragCode)
{
	const char* vertShaderCode = vertCode;
	const char* fragShaderCode = fragCode;
	// now create shader object from source code
	Render::Shader shader;
	shader.Compile(vertShaderCode, fragShaderCode);
	return shader;
}

Render::Texture Common::ResourceManager::LoadTextureFromFile(const char* file)
{
	// create texture object
	Render::Texture texture;

	// load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

	if (nrChannels == 4) // Alpha should be true for PNG images and false for JPG
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // RGBA compatible
		texture._internalFormat = GL_RGBA;
		texture._imageFormat = GL_RGBA;
	}
	else
	{
		// assume RGB
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // RGB compatible
		texture._internalFormat = GL_RGB;
		texture._imageFormat = GL_RGB;
	}

	// now generate texture
	texture.Generate(width, height, data);
	// free image data
	stbi_image_free(data);
	return texture;
}

Render::Texture Common::ResourceManager::LoadTextureFromFile(std::filesystem::path file)
{
	// create texture object
	Render::Texture texture;

	// load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file.string().c_str(), &width, &height, &nrChannels, 0);

	if (nrChannels == 4) // Alpha should be true for PNG images and false for JPG
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // RGBA compatible
		texture._internalFormat = GL_RGBA;
		texture._imageFormat = GL_RGBA;
	}
	else
	{
		// assume RGB
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // RGB compatible
		texture._internalFormat = GL_RGB;
		texture._imageFormat = GL_RGB;
	}

	// now generate texture
	texture.Generate(width, height, data);
	// free image data
	stbi_image_free(data);
	return texture;
}