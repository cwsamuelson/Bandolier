#ifndef BANDOLIER_OPEN_GL_SHADER_HH
#define BANDOLIER_OPEN_GL_SHADER_HH

#include <string>

#include <glad/glad.h>

#include "shader.hh"

namespace Bandolier {

class OpenGlShader : public Shader {
private:
  std::unordered_map<std::string, int> mUniformCache;
  std::string mName;

  int GetCached(const std::string& name);

  std::string ReadFile(const std::string& filePath);

  std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

  void Compile(const std::unordered_map<GLenum, std::string>& sources);

public:
  OpenGlShader(const std::string& filePath);

  OpenGlShader(std::string name, const std::string& vertexSource, const std::string& fragmentSource);

  virtual ~OpenGlShader();

  void Bind() const override;

  void Unbind() const override;

  std::string Name() const override;

  void SetUniform(const std::string& name, int value);

  void SetUniform(const std::string& name, float value);

  void SetUniform(const std::string& name, const glm::vec2& value);

  void SetUniform(const std::string& name, const glm::vec3& value);

  void SetUniform(const std::string& name, const glm::vec4& value);

  void SetUniform(const std::string& name, const glm::mat2& value);

  void SetUniform(const std::string& name, const glm::mat3& value);

  void SetUniform(const std::string& name, const glm::mat4& value);
};

}

#endif //BANDOLIER_OPEN_GL_SHADER_HH
