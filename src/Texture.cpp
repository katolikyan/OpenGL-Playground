#include "Texture.hpp"
#include <GL/glew.h>
#include "stb_image.hpp"

Texture::Texture(const std::string& path) : \
  m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), \
  m_Width(0), m_Height(0), m_BPP(0) 
{

  stbi_set_flip_vertically_on_load(1);
  m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

  glGenTextures(1, &m_RendererID);
  glBindTexture(GL_TEXTURE_2D, m_RendererID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT/*GL_CLAMP_TO_EDGE*/);
                                                    // GL_REPEAT for tailing

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, \
               GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
  glBindTexture(GL_TEXTURE_2D, 0);

  if (m_LocalBuffer)
    stbi_image_free(m_LocalBuffer);
}

Texture::~Texture() {
  glDeleteTextures(1, &m_RendererID);
}


void Texture::Bind(unsigned int slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
}

inline int Texture::GetWidth() const {
  return m_Width;
}

inline int Texture::GetHeight() const {
  return m_Height;
}