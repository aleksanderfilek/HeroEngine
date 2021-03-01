#include"H_mesh.hpp"

namespace Hero
{
    Mesh::Mesh()
    {
        this->_vertices = nullptr;
        this->_verticesCount = 0;

        this->_indices = nullptr;
        this->_indicesCount = 0;
    }

    Mesh::~Mesh()
    {
        delete[] this->_vertices;
        this->_vertices = nullptr;
        this->_verticesCount = 0;

        delete[] this->_indices;
        this->_indices = nullptr;
        this->_indicesCount = 0;

        glDeleteVertexArrays(1, &this->_VAO);
        glDeleteBuffers(1, &this->_VBO);
        glDeleteBuffers(1, &this->_EBO);
    }

    void Mesh::SetVertices(Vertex* vertices, unsigned int count)
    {
        this->_vertices = vertices;
        this->_verticesCount = count;
    }

    void Mesh::SetIndices(unsigned int* indices, unsigned int count)
    {
        this->_indices = indices;
        this->_indicesCount = count;
    }

    void Mesh::Load(const std::string& path)
    {
        std::ifstream readFile;
        readFile.open(path.c_str(), std::ios::in | std::ios::binary);

        if(!readFile.is_open())
        {
            std::cout<<"Could not create the file: "<<path<<std::endl;
            return;
        }

        int positionCount = 0;
        readFile.read((char*)&positionCount, sizeof(int));
        float* positions = new float[positionCount];
        readFile.read((char*)positions, positionCount*sizeof(float));

        int normalCount = 0;
        readFile.read((char*)&normalCount, sizeof(int));
        float* normals = new float[normalCount];
        readFile.read((char*)normals, normalCount*sizeof(float));

        int uvCount = 0;
        readFile.read((char*)&uvCount, sizeof(int));
        float* uvs = new float[uvCount];
        readFile.read((char*)uvs, uvCount*sizeof(float));

        int faceCount = 0;
        readFile.read((char*)&faceCount, sizeof(int));
        int* faces = new int[9*faceCount];
        readFile.read((char*)faces, 9*faceCount*sizeof(int));

        readFile.close();

        
        Vertex* vertices = new Vertex[3*faceCount];

        for(int i = 0, j = 0; i < 9*faceCount; i+=3)
        {
            float3 position = {
                    positions[3*faces[i]+0], 
                    positions[3*faces[i]+1], 
                    positions[3*faces[i]+2]
                    };
            float3 normal = {
                    normals[3*faces[i + 1] + 0], 
                    normals[3*faces[i + 1] + 1], 
                    normals[3*faces[i + 1] + 2]
                    };
            float2 uv = {
                    uvs[2*faces[i+2]+0],
                    uvs[2*faces[i+2]+1]
                    };
            vertices[j] = {position, normal, uv};
            j++; 
        }

        unsigned int* indices = new unsigned int[3*faceCount];

        for(int i = 0; i < 3*faceCount; i++)
        {
            indices[i]=i;
        }

        delete[] positions;
        delete[] normals;
        delete[] uvs;
        delete[] faces;

        this->SetVertices(vertices, 3*faceCount);
        this->SetIndices(indices, 3*faceCount);
        this->Generate();
    }

    void Mesh::Generate()
    {
        glGenVertexArrays(1, &this->_VAO);
        glGenBuffers(1, &this->_VBO);
        glGenBuffers(1, &this->_EBO);

        glBindVertexArray(this->_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
        glBufferData(GL_ARRAY_BUFFER, this->_verticesCount * sizeof(Vertex), &this->_vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indicesCount * sizeof(unsigned int), &this->_indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

        glBindVertexArray(0);
    }

    void Mesh::Draw()
    {
        glBindVertexArray(this->_VAO);
        //glDrawArrays(GL_TRIANGLES, 0, this->_verticesCount);
        glDrawElements(GL_TRIANGLES, this->_indicesCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}