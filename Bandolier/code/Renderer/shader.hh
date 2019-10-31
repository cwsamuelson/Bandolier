#ifndef BANDOLIER_SHADER_HH
#define BANDOLIER_SHADER_HH

#include <unordered_map>
#include <string>
#include <memory>

#include "../../vendor/glm/glm/glm.hpp"

namespace Bandolier {

class Shader
{
protected:
  uint32_t mID;

public:
  ~Shader() = default;

  virtual void
  Bind() const = 0;

  virtual void
  Unbind() const = 0;

  virtual std::string
  Name() const = 0;

  static std::shared_ptr<Shader>
  Create(std::string name, const std::string& vertexSource, const std::string& fragmentSource);
  static std::shared_ptr<Shader>
  Create(const std::string& filePath);
};

class ShaderLibrary
{
private:
  std::unordered_map<std::string, std::shared_ptr<Shader>> mShaders;

public:
  void Add(const std::shared_ptr<Shader>& shader);
  void Add(const std::string& name, const std::shared_ptr<Shader>& shader);

  std::shared_ptr<Shader> Load(const std::string& filePath);
  std::shared_ptr<Shader> Load(const std::string& name, const std::string& filePath);

  std::shared_ptr<Shader> Get(const std::string& name);

  bool Exists(const std::string& name);
};

}

#endif //BANDOLIER_SHADER_HH
