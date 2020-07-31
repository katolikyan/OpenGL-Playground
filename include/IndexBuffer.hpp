#ifndef __OBJ_VIEWER_INCLUDE_INDEXBUFFER_CLASS_HPP__
# define __OBJ_VIEWER_INCLUDE_INDEXBUFFER_CLASS_HPP__
class IndexBuffer
{
  private:
    unsigned int m_RendererID;
    unsigned int m_Count;

  public:      
    IndexBuffer(const void * data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};

#endif