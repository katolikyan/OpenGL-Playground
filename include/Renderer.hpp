#pragma once

#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

class Renderer {

  public:
    Renderer(void);
    ~Renderer(void);

    void Clear() const;
    void DrawElements(const VertexArray& ca, const IndexBuffer& ib, const Shader& shader) const;
    void DrawArrays(const VertexArray& ca, const Shader& shader, unsigned int count) const;

  private:
};