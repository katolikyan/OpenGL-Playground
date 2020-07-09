#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"
#include <assert.h>

VertexBufferLayout::VertexBufferLayout() : m_Stride(0) {}

VertexBufferLayout::~VertexBufferLayout() {};

template<typename T>
void VertexBufferLayout::Push(unsigned int count) {
  assert(false);
}

template<>
void VertexBufferLayout::Push<float>(unsigned int count) {
  m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
  m_Stride += count * GetSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
  m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_Stride += count * GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
  m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
  m_Stride += count * GetSizeOfType(GL_UNSIGNED_INT);
}

const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const { 
  return m_Elements; 
}

unsigned int VertexBufferLayout::GetStride() const { 
  return m_Stride;
}