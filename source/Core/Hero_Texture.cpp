#include"Core/Hero_Texture.hpp"

namespace Hero
{

Texture* LoadTexture(const std::string& path, std::uint8_t textureFlags)
{
    Texture* texture = new Texture();

    *texture = Extra::LoadTextureByCopy(path, textureFlags);

    return texture;
}

void UnloadTexture(Texture* texture)
{
    glDeleteTextures(1, &texture->glId);
    DEBUG_CODE( glCheckError(); )
    delete texture;
}

void BindTexture(const Texture* texture)
{
    glActiveTexture(GL_TEXTURE0);
    DEBUG_CODE( glCheckError(); )
    glBindTexture(GL_TEXTURE_2D, texture->glId);
    DEBUG_CODE( glCheckError(); )
}

void UnbindTexture()
{
    glDisable(GL_TEXTURE_2D);
    DEBUG_CODE( glCheckError(); )
}

namespace Extra
{

Texture LoadTextureByCopy(const std::string& path, uint8_t textureFlags)
{
    // load texture from file
    int width, height;
    unsigned char *image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    if(!image)
    {
        std::cout<<"Could not load texture: "<<path<<std::endl;
        exit(-1);
    }

    unsigned int gl_id;
    glGenTextures(1, &gl_id);
    DEBUG_CODE( glCheckError(); )
    glBindTexture(GL_TEXTURE_2D, gl_id);
    DEBUG_CODE( glCheckError(); )
    
    int param = (textureFlags & 1)?GL_LINEAR: GL_NEAREST;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    DEBUG_CODE( glCheckError(); )

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    DEBUG_CODE( glCheckError(); )

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
        GL_RGB, GL_UNSIGNED_BYTE, image);
    DEBUG_CODE( glCheckError(); )

    if(textureFlags & 128){
        glGenerateMipmap(GL_TEXTURE_2D);
        DEBUG_CODE( glCheckError(); )
    }

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    DEBUG_CODE( glCheckError(); )

    Texture texture;

    texture.glId = gl_id;
    texture.size = { width, height };
    texture.name = path;

    return texture;
}

void UnloadTextureByCopy(Texture& texture)
{
    glDeleteTextures(1, &texture.glId);
    DEBUG_CODE( glCheckError(); )
}

}

}