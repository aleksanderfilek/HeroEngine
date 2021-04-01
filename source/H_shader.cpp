#include"H_shader.hpp"

namespace Hero
{

    Shader::~Shader()
    {
        glDeleteProgram(this->glID);
        glCheckError();
        this->glID = 0;
    }

    void Shader::Load(const std::string& path)
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
            
            int  success;
            char infoLog[512];
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            glAttachShader(program, vertex);
            glGetProgramiv(program, GL_ATTACHED_SHADERS, &success);
            if(!success)
            {
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                std::cout << "ERROR::PROGRAM::VERTEX::ATTACHED_FAILED\n" << infoLog << std::endl;
            }
        }

        if(fragmentSize > 0){
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, (const char**)&fragmentCode, NULL);
            glCompileShader(fragment);

            int  success;
            char infoLog[512];
            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(fragment, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            glAttachShader(program, fragment);
            glGetProgramiv(program, GL_ATTACHED_SHADERS, &success);
            if(!success)
            {
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                std::cout << "ERROR::PROGRAM::FRAGMENT::ATTACHED_FAILED\n" << infoLog << std::endl;
            }
        }

        if(geometrySize > 0){
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, (const char**)&geometryCode, NULL);
            glCompileShader(geometry);

            int  success;
            char infoLog[512];
            glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(geometry, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            glAttachShader(program, geometry);
            glGetProgramiv(program, GL_ATTACHED_SHADERS, &success);
            if(!success)
            {
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                std::cout << "ERROR::PROGRAM::GEOMETRY::ATTACHED_FAILED\n" << infoLog << std::endl;
            }
        }

        glLinkProgram(program);
        int  success;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        if(vertexSize > 0){
            glDeleteShader(vertex);
            delete[] vertexCode;
        }
        if(fragmentSize > 0){
            glDeleteShader(fragment);
            delete[] fragmentCode;
        }
        if(geometrySize > 0){
            glDeleteShader(geometry);
            delete[] geometryCode;
        }

        this->glID = program;
    }

    void Shader::Bind()
    {
        glUseProgram(this->glID);
        glCheckError();
    }

    unsigned int Shader::GetGlID()
    {
        return this->glID;
    }

    unsigned int Shader::GetUniformLocation(const char* uniformName)
    {
        return glGetUniformLocation(this->glID, uniformName);
    }
}