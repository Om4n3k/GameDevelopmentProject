//
// Created by omank on 7.12.2025.
//

#include "Texture.h"

#include "Engine.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

#include "graphics/Texture.h"

namespace eng {
    Texture::Texture(int width, int height, int numChannels, const unsigned char *data) {
        Init(width, height, numChannels, data);
    }

    Texture::~Texture() {
        if (m_TextureId <= 0) return;
        glDeleteTextures(1, &m_TextureId);
    }

    GLuint Texture::GetId() const {
        return m_TextureId;
    }

    void Texture::Init(int width, int height, int numChannels, const unsigned char* data) {
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

    std::shared_ptr<Texture> Texture::Load(const std::string &path) {
        int width, height, numChannels;

        auto &fs = Engine::GetInstance().GetFileSystem();
        auto fullPath = fs.GetAssetsFolder() / path;
        if (!std::filesystem::exists(fullPath)) {
            return nullptr;
        }

        std::shared_ptr<Texture> result;
        unsigned char *data = stbi_load(fullPath.string().c_str(), &width, &height, &numChannels, 0);
        if (data) {
            result = std::make_shared<Texture>(width, height, numChannels, data);
            stbi_image_free(data);
        } else {
            std::cerr << "Failed to load texture at path: " << fullPath << std::endl;
        }
        return result;
    }
} // eng