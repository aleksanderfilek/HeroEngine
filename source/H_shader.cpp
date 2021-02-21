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

        FILE* file = fopen(path, "r");

        if(file == NULL){
            printf("Imposible to open the file!\n");
            return -1;
        }

        unsigned int vertex_shader_size = 1024;
        unsigned int vertex_shader_used_bytes = 0;
        char* vertex_shader_code = (char*)calloc(vertex_shader_size, sizeof(char));

        size_t fragment_shader_size = 1024;
        size_t fragment_shader_used_bytes = 0;
        char* fragment_shader_code = (char*)calloc(fragment_shader_size, sizeof(char));

        int shader_type = -1;

        char chunk[128];

        while(fgets(chunk, sizeof(chunk), file) != NULL)
        {
            if(strstr(chunk, "// vertex") != NULL)
            {
                shader_type = 0;
                //continue;
            }
            else if(strstr(chunk, "// fragment") != NULL)
            {
                shader_type = 1;
                //continue;
            }

            switch (shader_type)
            {
            case 0:
                    if((vertex_shader_size - vertex_shader_used_bytes) < strlen(chunk)){
                        vertex_shader_code = (char*)realloc(vertex_shader_code, vertex_shader_size + 1024);
                        vertex_shader_size += 1024;
                    }
                    strcat(vertex_shader_code, chunk);
                    vertex_shader_used_bytes += strlen(chunk);
                break;  
            case 1:
                    if((fragment_shader_size - fragment_shader_used_bytes) < strlen(chunk)){
                        fragment_shader_code = (char*)realloc(fragment_shader_code, fragment_shader_size + 1024);
                        fragment_shader_size += 1024;
                    }
                    strcat(fragment_shader_code, chunk);
                    fragment_shader_used_bytes += strlen(chunk);
                break;
            }
        }

        fclose(file);

        // Create shader program
        int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, (const char**)&vertex_shader_code, NULL);
        glCompileShader(vertex);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, (const char**)&fragment_shader_code, NULL);
        glCompileShader(fragment);

        unsigned int program = glCreateProgram();
        glAttachShader(program,vertex);
        glAttachShader(program,fragment);
        glLinkProgram(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        free(vertex_shader_code);
        free(fragment_shader_code);

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

            this->name = (char**)realloc(this->name, this->allocatedElements * sizeof(char*));
            this->glId = (unsigned int*)realloc(this->glId, this->allocatedElements * sizeof(unsigned int));

            index = this->allocatedElements - 1; // get new index
        }

        this->name[index] = (char*)malloc(strlen(path)+1);
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