#include"Core/Hero_Resources.hpp"

namespace Hero
{

Texture* LoadTexture(const std::string& path, std::uint8_t textureFlags)
{
    // load texture from file
    int width, height;
    unsigned char *image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    if(!image)
    {
        std::cout<<"Could not load texture: "<<path<<std::endl;
        return nullptr;
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

    Texture* texture = new Texture();

    texture->glId = gl_id;
    texture->size = { width, height };
    texture->name = path;

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

Shader* LoadShader(const std::string& path)
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

    Shader* shader = new Shader();

    shader->glId = program;

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

Mesh* LoadMeshRef(const std::string& path)
{
    return nullptr;
}

Mesh LoadMesh(const std::string& path)
{
    Mesh mesh;
    return mesh;
}

void UnloadMeshRef(Mesh* mesh)
{
    for(auto buff: mesh->buffers)
    {
       free(buff.array);
    }
    mesh->buffers.clear();

    free(mesh->indices.array);

    glDeleteBuffers(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
    free(mesh);
}

void UnloadMesh(Mesh& mesh)
{
    for(auto buff: mesh.buffers)
    {
       free(buff.array);
    }
    mesh.buffers.clear();

    free(mesh.indices.array);

    glDeleteBuffers(1, &mesh.VAO);
    glDeleteBuffers(1, &mesh.VBO);
    glDeleteBuffers(1, &mesh.EBO);
}

void DrawMesh(const Mesh* mesh)
{
    glBindVertexArray(mesh->VAO);
    DEBUG_CODE( glCheckError(); )
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glCheckError();
    glBindVertexArray(0);
    DEBUG_CODE( glCheckError(); )
}

void GenerateMesh(Mesh* mesh)
{
    int buffSize = 0;
    for(auto& buff: mesh->buffers)
    {
        buffSize += buff.length;
    }

    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);
    DEBUG_CODE( glCheckError(); )
    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), mesh->buffers[0].array, GL_STATIC_DRAW);  
    DEBUG_CODE( glCheckError(); )
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(uint32_t), mesh->indices.array, GL_STATIC_DRAW);
    DEBUG_CODE( glCheckError(); )
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    /*glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, buffSize * sizeof(float), NULL, GL_STATIC_DRAW);  
    DEBUG_CODE( glCheckError(); )
    uint32_t buffOffset = 0;
    for(auto& buff: mesh->buffers)
    {
        uint32_t size = buff.length * sizeof(float);
        glBufferSubData(GL_ARRAY_BUFFER, buffOffset, size, buff.array);
        DEBUG_CODE( glCheckError(); )
        buffOffset += size;
    }

    buffOffset = 0;
    for(int i = 0; i < mesh->buffers.size(); i++)
    {
        meshBufferF& buff = mesh->buffers[i];
        glVertexAttribPointer(0, (uint32_t)buff.type, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)buffOffset);
        DEBUG_CODE( glCheckError(); )
        buffOffset += buff.length * sizeof(float);
        std::cout<<i<<std::endl;
    }

    for(int i = 0; i < mesh->buffers.size(); i++)
    {
        //glVertexAttribDivisor(i, 1);
        DEBUG_CODE( glCheckError(); )
    }
*/
}

}