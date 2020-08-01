#ifndef __OBJ_VIEWER_INCLUDE_OBJLOAD_CLASS_HPP__
# define __OBJ_VIEWER_INCLUDE_OBJLOAD_CLASS_HPP__

#include <string>
#include <vector>
#include "Mesh.class.hpp"

class ObjLoad {
  
  public:
    ObjLoad(const std::string& filepath);
    ObjLoad();
    ~ObjLoad();

    std::vector<Vertex> GetVertices() const;

  private:
    void ParseObj(const std::string& filepath);
    std::vector<Vertex>        m_Vertices;
    std::string m_FilePath;
};

#endif