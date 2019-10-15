#ifndef BANDOLIER_SHADER_HH
#define BANDOLIER_SHADER_HH

#include <unordered_map>
#include <string>
#include "../../vendor/glm/glm/glm.hpp"

namespace Bandolier {

class Shader
{
private:
  uint32_t mID;
  std::unordered_map<std::string, int> mUniformCache;

  int
  GetCached(const std::string& name);

public:
  Shader(const std::string& vertexSource, const std::string& fragmentSource);

  ~Shader();

  void
  Bind() const;

  void
  Unbind() const;

  void
  UploaduniformMat4(const std::string& name, const glm::mat4& matrix);
};

}

#endif //BANDOLIER_SHADER_HH
