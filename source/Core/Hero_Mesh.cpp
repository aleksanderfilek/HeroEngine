#include"Core/Hero_Mesh.hpp"

namespace Hero
{

Mesh* LoadMesh(const std::string& path)
{
    return nullptr;
}

void UnloadMesh(Mesh* mesh)
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

void DrawMesh(const Mesh* mesh)
{
    glBindVertexArray(mesh->VAO);
    DEBUG_CODE( glCheckError(); )
    glDrawElements(GL_TRIANGLES, mesh->indices.length, GL_UNSIGNED_INT, 0);
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
    /*glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), mesh->buffers[0].array, GL_STATIC_DRAW);  
    DEBUG_CODE( glCheckError(); )*/
    /*glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);*/

    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.length * sizeof(uint32_t), mesh->indices.array, GL_STATIC_DRAW);
    DEBUG_CODE( glCheckError(); )

    buffOffset = 0;
    for(int i = 0; i < mesh->buffers.size(); i++)
    {
        meshBufferF& buff = mesh->buffers[i];
        glEnableVertexAttribArray(i);	
        glVertexAttribPointer(i, (uint32_t)buff.type, GL_FLOAT, GL_FALSE, (uint32_t)buff.type * sizeof(float), (void*)buffOffset);
        DEBUG_CODE( glCheckError(); )
        buffOffset += buff.length * sizeof(float);
    }
    glBindVertexArray(0);
/*
    for(int i = 0; i < mesh->buffers.size(); i++)
    {
        //glVertexAttribDivisor(i, 1);
        DEBUG_CODE( glCheckError(); )
    }
*/
}

namespace Extra
{

Mesh LoadMeshByCopy(const std::string& path)
{
    Mesh mesh;

    return mesh;
}

void UnloadMeshByCopy(Mesh& mesh)
{
    
}

}

}