#pragma once 

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
  private:
    unsigned int m_RendererID;

  public:
    VertexArray(void);
    ~VertexArray(void);

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layot);
    void Bind() const;
    void Unbind() const;
};