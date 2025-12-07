//
// Created by omank on 7.12.2025.
//

#include "Texture.h"

namespace eng {
    Texture::Texture(int width, int height, int numChannels, const unsigned char *data) {
        m_Height = height;
        m_Width = width;
        m_NumChannels = numChannels;

        glGenTextures(1, &m_TextureId);
        glBindTexture(GL_TEXTURE_2D, m_TextureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture::~Texture() {
        if (m_TextureId <= 0) return;
        glDeleteTextures(1, &m_TextureId);
    }

    GLuint Texture::GetId() const {
        return m_TextureId;
    }
} // eng