#pragma once

#include <string>
#include <unordered_map>
#include "Mat4.class.hpp"
#include "../glm/glm.hpp"

struct ShaderProgramSource {
    std::string VertexShader;
    std::string FragmentShader;
};

class Shader {

  private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
    

    unsigned int GetUniformLocation(const std::string& name);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    ShaderProgramSource ParseShader(const std::string path);
    bool CompileShader();

  public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // set uniforms
    void SetUniformMat4f(const std::string& name, glm::mat4 matrix);
    void SetUniformMat4f(const std::string& name, Mat4 matrix);
    void SetUniform1i(const std::string& name, int v0);
    void SetUniform1f(const std::string& name, float v0);
    void SetUniform4f(const std::string& name, \
                      float v0, float v1, float v2, float v3);
};