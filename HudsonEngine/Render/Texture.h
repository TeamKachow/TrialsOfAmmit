#pragma once
#include "../Util/stdafx.h"

namespace Hudson::Render {
    class Texture
    {
    public:
        // holds the ID of the texture object
        unsigned int ID;
        // texture image dimensions
        unsigned int _width, _height;
        // texture format
        unsigned int _internalFormat; // format of texture object
        unsigned int _imageFormat; // format of loaded image
        // texture configuration
        unsigned int _wrapS; // wrapping mode on S axis
        unsigned int _wrapT; // wrapping mode on T axis
        unsigned int _filterMin; // filtering mode if texture pixels < screen pixels
        unsigned int _filterMax; // filtering mode if texture pixels > screen pixels

        // constructor
        Texture();
        // generates texture from image data
        void Generate(unsigned int width, unsigned int height, unsigned char* data);
        void Generate(unsigned int width, unsigned int height, std::filesystem::path data);
        // binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;
    };
}
