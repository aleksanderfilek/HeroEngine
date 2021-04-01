#include"H_texture.hpp"

namespace Hero
{
    unsigned int Texture::bindedTexturesCount = 0;

    Texture::Texture()
    {

    }

    Texture::Texture(const std::string& path)
    {
        this->Load(path);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &this->glId);
    }

    void Texture::Load(const std::string& path)
    {
        // load texture from file
        int width, height;
        unsigned char *image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

        if(!image)
        {
            std::cout<<"Could not load texture: "<<path<<std::endl;
            return;
        }

        unsigned int gl_id;
        glGenTextures(1, &gl_id);
        glBindTexture(GL_TEXTURE_2D, gl_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
            GL_RGB, GL_UNSIGNED_BYTE, image);
        glCheckError();
        glGenerateMipmap(GL_TEXTURE_2D);
        glCheckError();
        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0);
        glCheckError();

        this->glId = gl_id;
        this->size = { width, height };
    }

    void Texture::Bind()
    {
        glActiveTexture(GL_TEXTURE0 + Texture::bindedTexturesCount);
        glCheckError();
        glBindTexture(GL_TEXTURE_2D, this->glId);
        glCheckError();        
        Texture::bindedTexturesCount++;
    }

    void Texture::Unbind()
    {
        glDisable(GL_TEXTURE_2D);
        Texture::bindedTexturesCount = 0;
    }

    int2 Texture::GetSize()
    {
        return this->size;
    }
    
    unsigned int Texture::GetGlID()
    {
        return this->glId;
    }

}