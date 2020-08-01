#include "ObjLoad.class.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>

ObjLoad::ObjLoad(const std::string& filepath) {
  m_FilePath = filepath;
  ParseObj(filepath);
}

ObjLoad::~ObjLoad() {

}

void ObjLoad::ParseObj(const std::string& filepath) {
  //std::ifstream fin;
  FILE *fin = fopen(filepath.c_str(), "r");
  char line[128];
  std::vector<glm::vec3> v;
  std::vector<glm::vec3> vn;
  std::vector<glm::vec2> vt;

  //while(getline(stream, line)) {
  while(1) {
    if (fscanf(fin, "%s", line) == EOF)
      break;

    if (strcmp(line, "v") == 0) {
      glm::vec3 vertex;
      fscanf(fin, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      v.push_back(vertex);
    }
    else if (strcmp(line, "vt") == 0) {
      glm::vec2 uv;
      fscanf(fin, "%f %f\n", &uv.x, &uv.y);
      vt.push_back(uv);
    }
    else if (strcmp(line, "vn") == 0) {
      glm::vec3 normal;
      fscanf(fin, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
      vn.push_back(normal);
    }
    else if (strcmp(line, "f") == 0 ) {
      //std::string vertex1, vertex2, vertex3;
      unsigned int vi[3], vti[3], vni[3];
      int matches = fscanf(fin, "%d/%d/%d %d/%d/%d %d/%d/%d\n", \
                           &vi[0], &vti[0], &vni[0], \
                           &vi[1], &vti[1], &vni[1], \
                           &vi[2], &vti[2], &vni[2]);
      if (matches != 9){
          std::cout << "File can't be read" << std::endl;
          return;
      }
      //push 3 vertexes. 
      m_Vertices.push_back({v[vi[0] - 1], vn[vni[0] - 1], vt[vti[0] - 1]});
      m_Vertices.push_back({v[vi[1] - 1], vn[vni[1] - 1], vt[vti[1] - 1]});
      m_Vertices.push_back({v[vi[2] - 1], vn[vni[2] - 1], vt[vti[2] - 1]});
    }
  }
}

std::vector<Vertex>  ObjLoad::GetVertices() const {
  return m_Vertices;
}