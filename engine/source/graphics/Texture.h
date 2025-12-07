//
// Created by omank on 7.12.2025.
//

#ifndef GAMEDEVELOPMENTPROJECT_TEXTURE_H
#define GAMEDEVELOPMENTPROJECT_TEXTURE_H
#include <memory>

#include "GL/glew.h"

namespace eng {
    class Texture {
    public:
        Texture(int width, int height, int numChannels, const unsigned char* data);
        ~Texture();
        GLuint GetId() const;
        void Init(int width, int height, int numChannels, const unsigned char* data);

        static std::shared_ptr<Texture> Load(const std::string& path);
    private:
        int m_Width = 0;
        int m_Height = 0;
        int m_NumChannels = 0;
        GLuint m_TextureId = 0;
    };
} // eng

#endif //GAMEDEVELOPMENTPROJECT_TEXTURE_H