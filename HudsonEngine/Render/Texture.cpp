#include "../Render/Texture.h"

using namespace Hudson::Render;

Texture::Texture() {
    _width = 0;
    _height = 0;
    _internalFormat = GL_RGB;
    _imageFormat = GL_RGB;
    _wrapS = GL_REPEAT;
    _wrapT = GL_REPEAT;
    _filterMin = GL_NEAREST;
    _filterMax = GL_NEAREST;

    glGenTextures(1, &this->ID);
};

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->_width = width;
    this->_height = height;
    // create Texture

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->_internalFormat, width, height, 0, this->_imageFormat, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->_wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->_wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->_filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->_filterMax);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}