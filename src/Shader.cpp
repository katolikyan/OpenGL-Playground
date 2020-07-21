#include "Shader.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <unordered_map>
#include "Mat4.class.hpp"

Shader::Shader(const std::string& filepath) : \
                m_FilePath(filepath), m_RendererID(0) {
  ShaderProgramSource source = ParseShader(filepath);
  m_RendererID = CreateShader(source.VertexShader, source.FragmentShader);
}

Shader::~Shader() {
  glDeleteProgram(m_RendererID);
}

unsigned int Shader::GetUniformLocation(const std::string& name) {
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    return m_UniformLocationCache[name];

  int location = glGetUniformLocation(m_RendererID, name.c_str());
  if (location == -1)
    std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
  m_UniformLocationCache[name] = location;
  return location;
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4 matrix) {
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}
void Shader::SetUniformMat4f(const std::string& name, Mat4 matrix) {
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0]);
}

void Shader::SetUniform1i(const std::string& name, int v0) {
  glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetUniform1f(const std::string& name, float v0) {
  glUniform1f(GetUniformLocation(name), v0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
  glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::Bind() const {
  glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
  glUseProgram(0);
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram(); 
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = (char *)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

ShaderProgramSource Shader::ParseShader(const std::string path) {
  std::ifstream stream(path);
  enum class ShaderType {
      None = -1, Vertex =  0, Fragment = 1
  };

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::None;

  while(getline(stream, line)) {
      if (line.find("#shader") != std::string::npos) {
          if (line.find("vertex") != std::string::npos)
              type = ShaderType::Vertex;
          else if (line.find("fragment") != std::string::npos)
              type = ShaderType::Fragment;
      }
      else {
          ss[(int)type] << line << '\n';
      }
  }
  return { ss[0].str(), ss[1].str() };
}