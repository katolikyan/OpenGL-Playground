#ifndef __OBJ_VIEWER_INCLUDE_RENDERER_CLASS_HPP__
# define __OBJ_VIEWER_INCLUDE_RENDERER_CLASS_HPP__

#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Mesh.class.hpp"

class Renderer {

  public:
    Renderer(void);
    ~Renderer(void);

    void Clear() const;
    void Clear(unsigned int flags[], unsigned int count) const;
    void ClearColor(float r, float g, float b, float a) const;
    void DrawElements(const VertexArray& ca, const IndexBuffer& ib, const Shader& shader) const;
    void DrawElements(const Mesh& mesh, const Shader& shader) const;
    void DrawArrays(const VertexArray& ca, const Shader& shader, unsigned int count) const;

  private:
};

#endif