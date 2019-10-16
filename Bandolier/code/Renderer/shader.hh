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

  static std::shared_ptr<Shader>
  Create(const std::string& vertexSource, const std::string& fragmentSource);
};

}

#endif //BANDOLIER_SHADER_HH
