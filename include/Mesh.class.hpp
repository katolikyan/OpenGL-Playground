#ifndef __OBJ_VIEWER_INCLUDE_MESH_CLASS_HPP__
# define __OBJ_VIEWER_INCLUDE_MESH_CLASS_HPP__

#include "../glm/glm.hpp"
#include <vector>
#include <string>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct MeshTexture {
    unsigned int id;
    std::string type;
};  

class Mesh {

  public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
    Mesh(const Mesh& other);
    ~Mesh();
    Mesh& operator=(const Mesh& other);

    void Bind() const;
    unsigned int GetCountIB() const;
    std::vector<Vertex>        m_vertices;
    std::vector<unsigned int>   m_indices;
    std::vector<MeshTexture>   m_textures;

  private:

    VertexArray        *m_va;
    VertexBuffer       *m_vb;
    VertexBufferLayout *m_layout;
    IndexBuffer        *m_ib;
    void SetUpMesh();
};

#endif