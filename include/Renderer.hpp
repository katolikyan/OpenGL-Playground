#pragma once

#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

class Renderer {

  public:
    Renderer(void);
    ~Renderer(void);

    void Clear() const;
    void Draw(const VertexArray& ca, const IndexBuffer& ib, const Shader& shader) const;

  private:
};