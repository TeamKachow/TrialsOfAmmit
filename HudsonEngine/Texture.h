#pragma once

#include <glad/glad.h>

namespace Hudson::Render {
    class Texture
    {
    public:
        // holds the ID of the texture object
        unsigned int ID;
        // texture image dimensions
        unsigned int width, height;
        // texture format
        unsigned int internalFormat; // format of texture object
        unsigned int imageFormat; // format of loaded image
        // texture configuration
        unsigned int wrapS; // wrapping mode on S axis
        unsigned int wrapT; // wrapping mode on T axis
        unsigned int filterMin; // filtering mode if texture pixels < screen pixels
        unsigned int filterMax; // filtering mode if texture pixels > screen pixels

        // constructor
        Texture();
        // generates texture from image data
        void Generate(unsigned int width, unsigned int height, unsigned char* data);
        // binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;
    };
}
