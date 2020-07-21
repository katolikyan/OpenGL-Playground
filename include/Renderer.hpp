#pragma once

#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

class Renderer {

  public:
    Renderer(void);
    ~Renderer(void);

    void Clear() const;
    void Clear(unsigned int flags[], unsigned int count) const;
    void ClearColor(float r, float g, float b, float a) const;
    void DrawElements(const VertexArray& ca, const IndexBuffer& ib, const Shader& shader) const;
    void DrawArrays(const VertexArray& ca, const Shader& shader, unsigned int count) const;

  private:
};