#ifndef BANDOLIER_SHADER_HH
#define BANDOLIER_SHADER_HH

#include <string>

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

private:
  uint32_t mID;
};

}

#endif //BANDOLIER_SHADER_HH
