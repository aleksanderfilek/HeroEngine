#include"H_shader.hpp"

namespace Hero
{
    ShaderManager::ShaderManager(unsigned int size)
    {        
        this->allocatedElements = size;
        this->name = new char*[size];
        this->glId = new unsigned int[size];
    }

    ShaderManager::~ShaderManager()
    {
        for(int i = 0; i < this->allocatedElements; i++)
        {
            if(this->name[i] == NULL){
                continue;
            }

            delete this->name[i];
            glDeleteProgram(this->glId[i]);
        }

        delete this->name;
        delete this->glId;
        this->allocatedElements = 0;
    }

    ShaderId ShaderManager::LoadShader(const char* path)
    {
        for(int i = 0; i < this->allocatedElements; i++)
        {
            if(this->name[i] != NULL && strcmp(path, this->name[i]) == 0)
            {
                return i;
            }
        }

        std::ifstream readFile;
        readFile.open(path, std::ios::in | std::ios::binary);

        size_t vertexSize = 0;
        char* vertexCode;
        readFile.read((char*)&vertexSize, sizeof(size_t));
        if(vertexSize > 0)
        {
            vertexCode = new char[vertexSize+1];
            readFile.read(vertexCode, vertexSize);
            vertexCode[vertexSize] = '\0';
        }

        size_t fragmentSize = 0;
        char* fragmentCode;
        readFile.read((char*)&fragmentSize, sizeof(size_t));
        if(fragmentSize > 0)
        {
            fragmentCode = new char[fragmentSize+1];
            readFile.read(fragmentCode, fragmentSize);
            fragmentCode[fragmentSize] = '\0';
        }

        size_t geometrySize = 0;
        char* geometryCode;
        readFile.read((char*)&geometrySize, sizeof(size_t));
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
        }

        if(fragmentSize > 0){
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, (const char**)&fragmentCode, NULL);
            glCompileShader(fragment);
        }

        if(geometrySize > 0){
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, (const char**)&geometryCode, NULL);
            glCompileShader(geometry);
        }

        if(vertexSize > 0) glAttachShader(program, vertex);
        if(fragmentSize > 0) glAttachShader(program, fragment);
        if(geometrySize > 0) glAttachShader(program, geometry);

        glLinkProgram(program);

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

        // Create shader
        int index;
        for(index = 0; index < this->allocatedElements; index++)
        {
            if(this->name[index] == NULL)
            {
                break;
            }
        }

        if(index == this->allocatedElements)
        {
            this->allocatedElements++;

            this->name = (char**)std::realloc(this->name, this->allocatedElements * sizeof(char*));
            this->glId = (unsigned int*)std::realloc(this->glId, this->allocatedElements * sizeof(unsigned int));

            index = this->allocatedElements - 1; // get new index
        }

        this->name[index] = new char[strlen(path)+1];
        strcpy(this->name[index], path);
        this->glId[index] = program;
        
        return index;
    }

    void ShaderManager::DeleteShader(ShaderId id)
    {
        if(this->name[id] == NULL)
        return;

        delete this->name[id];
        this->name[id] = NULL;
        glDeleteProgram(this->glId[id]);
    }

    void ShaderManager::BindShader(ShaderId id)
    {
        glUseProgram(this->glId[id]);
    }

    int ShaderManager::GetShaderId(const char* path)
    {
        for(int i = 0; i < this->allocatedElements; i++)
        {
            if(this->name[i] != NULL && strcmp(path, this->name[i]) == 0)
            {
                return i;
            }
        }

        return -1;
    }

    unsigned int ShaderManager::GetUniformLocation(ShaderId id, const char* uniformName)
    {
        return glGetUniformLocation(this->glId[id], uniformName);
    }
}