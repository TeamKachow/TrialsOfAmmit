#ifndef TEXTURE_H
#define TEXTURE_H

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
        Texture() : width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR) {
            glGenTextures(1, &this->ID);

        };
        // generates texture from image data
        void Generate(unsigned int width, unsigned int height, unsigned char* data) {
            this->width = width;
            this->height = height;
            // create Texture
            glBindTexture(GL_TEXTURE_2D, this->ID);
            glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
            // set Texture wrap and filter modes
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
            // unbind texture
            glBindTexture(GL_TEXTURE_2D, 0);
        };
        // binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const {
            glBindTexture(GL_TEXTURE_2D, this->ID);
        };
    };
}

#endif