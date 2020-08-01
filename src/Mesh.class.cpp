#include "Mesh.class.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures) {
  m_vertices = vertices;
  m_indices = indices;
  m_textures = textures;
  SetUpMesh();  
}

Mesh::Mesh(std::vector<Vertex> vertices) {
  m_vertices = vertices;
  SetUpMesh();  
}

Mesh::Mesh(const Mesh& other) {
  m_vertices = other.m_vertices;
  m_indices = other.m_indices;
  m_textures = other.m_textures;
  SetUpMesh();
}

Mesh::~Mesh() {
  if (m_va)
    delete m_va;
  if (m_vb)
    delete m_vb;
  if (m_ib)
    delete m_ib;
  if (m_layout)
    delete m_layout;
}

Mesh& Mesh::operator=(const Mesh& other) {
  m_vertices = other.m_vertices;
  m_indices = other.m_indices;
  m_textures = other.m_textures;
  if (m_va)
    delete m_va;
  if (m_vb)
    delete m_vb;
  if (m_ib)
    delete m_ib;
  if (m_layout)
    delete m_layout;
  SetUpMesh();
  return *this;
}

void Mesh::SetUpMesh() {
  m_va = new VertexArray();
  m_vb = new VertexBuffer(static_cast<void*>(m_vertices.data()), m_vertices.size() * sizeof(Vertex));
  m_layout = new VertexBufferLayout();
  m_layout->Push<float>(3);
  m_layout->Push<float>(3);
  m_layout->Push<float>(2);
  m_va->AddBuffer(*m_vb, *m_layout);
  if (!m_indices.empty())
    m_ib = new IndexBuffer(static_cast<void*>(m_indices.data()), m_indices.size() * sizeof(unsigned int));
}

void Mesh::Draw(const Shader& shader) const {
  shader.Bind();
  m_va->Bind();
  if (m_ib) {
    m_ib->Bind();
    glDrawElements(GL_TRIANGLES, m_ib->GetCount(), GL_UNSIGNED_INT, nullptr);
  }
  else
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}

void Mesh::Bind() const {
  m_va->Bind();
  m_ib->Bind();
}

unsigned int Mesh::GetCountIB() const {
  return m_ib->GetCount();
}