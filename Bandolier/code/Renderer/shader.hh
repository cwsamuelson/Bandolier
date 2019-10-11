#ifndef BANDOLIER_SHADER_HH
#define BANDOLIER_SHADER_HH

#include <string>
#include "../../vendor/glm/glm/glm.hpp"

namespace Bandolier {

class Shader
{
public:
  Shader(const std::string& vertexSource, const std::string& fragmentSource);

  ~Shader();

  void
  Bind() const;

  void
  Unbind() const;

  void
  UploaduniformMat4(const std::string& name, const glm::mat4& matrix);

private:
  uint32_t mID;
};

}

#endif //BANDOLIER_SHADER_HH
