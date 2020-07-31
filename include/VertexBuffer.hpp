#ifndef __OBJ_VIEWER_INCLUDE_VERTEXBUFFER_CLASS_HPP__
# define __OBJ_VIEWER_INCLUDE_VERTEXBUFFER_CLASS_HPP__

class VertexBuffer
{
  private:
    unsigned int m_RendererID;

  public:      
    VertexBuffer(const void * data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};

#endif