#pragma once

#include <string>

class Texture {

  public:
    Texture(const std::string& path);
    ~Texture();


    void Bind(unsigned int slot = 0) const;
    void Unbind() const; 

    inline int GetWidth() const;
    inline int GetHeight() const;

  private:
    unsigned int m_RendererID;    
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
};