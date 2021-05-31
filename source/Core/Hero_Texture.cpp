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

Texture TextureFromText(const std::string& text, Color& color, Font* font)
{
        if(text.length() == 0)
                return {0, {0,0}, ""};;

        SDL_Surface* surface = TTF_RenderText_Blended( font, text.c_str(), color );
        if( !surface)
        {
                std::cout<<"Unable to render text surface! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
                return {0, {0,0}, ""};
        }

        int mode = GL_RGB;
        if(surface->format->BytesPerPixel == 4)
                mode = GL_RGBA;

        unsigned int id;
        glGenTextures(1, &id);
        DEBUG_CODE(glCheckError();)
        glBindTexture(GL_TEXTURE_2D, id);
        DEBUG_CODE(glCheckError();)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
                                GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        DEBUG_CODE(glCheckError();)
        glBindTexture(GL_TEXTURE_2D, 0);
        DEBUG_CODE(glCheckError();)

        Texture texture;
        texture.glId = id;
        texture.size = {surface->w, surface->h};

        SDL_FreeSurface(surface);

        return texture;
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