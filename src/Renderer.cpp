#include "Renderer.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
  shader.Bind();
  va.Bind();
  ib.Bind();
  glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawArrays(const VertexArray& va, const Shader& shader, unsigned int count) const {
  shader.Bind();
  va.Bind();
  glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::Clear() const {
  glClear(GL_COLOR_BUFFER_BIT);
}