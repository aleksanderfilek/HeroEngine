#include"Core/Hero_Shader.hpp"

namespace Hero
{

Shader* LoadShader(const std::string& path)
{
    Shader* shader = new Shader();

    *shader = Extra::LoadShaderByCopy(path);

    return shader;
}

void UnloadShader(Shader* shader)
{
    glDeleteProgram(shader->glId);
    DEBUG_CODE( glProgramCheckError(shader->glId, GL_DELETE_STATUS); )
    delete shader;

}

void BindShader(const Shader* shader)
{
    glUseProgram(shader->glId);
    glCheckError();
}

namespace Extra
{

Shader LoadShaderByCopy(const std::string& path)
{
std::ifstream readFile;
    readFile.open(path, std::ios::in | std::ios::binary);

    std::uint32_t vertexSize = 0;
    char* vertexCode;
    readFile.read((char*)&vertexSize, sizeof(std::uint32_t));

    if(vertexSize > 0)
    {
        vertexCode = new char[vertexSize+1];
        readFile.read(vertexCode, vertexSize);
        vertexCode[vertexSize] = '\0';
    }

    std::uint32_t fragmentSize = 0;
    char* fragmentCode;
    readFile.read((char*)&fragmentSize, sizeof(std::uint32_t));
    if(fragmentSize > 0)
    {
        fragmentCode = new char[fragmentSize+1];
        readFile.read(fragmentCode, fragmentSize);
        fragmentCode[fragmentSize] = '\0';
    }

    std::uint32_t geometrySize = 0;
    char* geometryCode;
    readFile.read((char*)&geometrySize, sizeof(std::uint32_t));
    if(geometrySize > 0)
    {
        geometryCode = new char[geometrySize+1];
        readFile.read(geometryCode, geometrySize);
        geometryCode[geometrySize] = '\0';
    }

    readFile.close();

    // Create shader program
    unsigned int program = glCreateProgram();

    int vertex, fragment, geometry;

    if(vertexSize > 0){
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, (const char**)&vertexCode, NULL);
        glCompileShader(vertex);        

        DEBUG_CODE( glShaderCheckError(vertex, GL_COMPILE_STATUS); )

        glAttachShader(program, vertex);
        DEBUG_CODE( glProgramCheckError(program, GL_ATTACHED_SHADERS); )
    }

    if(fragmentSize > 0){
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, (const char**)&fragmentCode, NULL);
        glCompileShader(fragment);

        DEBUG_CODE( glShaderCheckError(fragment, GL_COMPILE_STATUS); )


        glAttachShader(program, fragment);
        DEBUG_CODE( glProgramCheckError(program, GL_ATTACHED_SHADERS); )
    }

    if(geometrySize > 0){
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, (const char**)&geometryCode, NULL);
        glCompileShader(geometry);

        DEBUG_CODE( glShaderCheckError(geometry, GL_COMPILE_STATUS); )


        glAttachShader(program, geometry);
        DEBUG_CODE( glProgramCheckError(program, GL_ATTACHED_SHADERS); )
    }

    glLinkProgram(program);
    int  success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    DEBUG_CODE( glProgramCheckError(program, GL_LINK_STATUS); )


    if(vertexSize > 0){
        glDeleteShader(vertex);
        DEBUG_CODE( glShaderCheckError(vertex, GL_DELETE_STATUS); )
        delete[] vertexCode;
    }
    if(fragmentSize > 0){
        glDeleteShader(fragment);
        DEBUG_CODE( glShaderCheckError(fragment, GL_DELETE_STATUS); )
        delete[] fragmentCode;
    }
    if(geometrySize > 0){
        glDeleteShader(geometry);
        DEBUG_CODE( glShaderCheckError(geometry, GL_DELETE_STATUS); )
        delete[] geometryCode;
    }

    Shader shader;

    shader.glId = program;

    return shader;
}

void UnloadShaderByCopy(Shader& shader)
{
    glDeleteProgram(shader.glId);
    DEBUG_CODE( glProgramCheckError(shader.glId, GL_DELETE_STATUS); )
}

}

}