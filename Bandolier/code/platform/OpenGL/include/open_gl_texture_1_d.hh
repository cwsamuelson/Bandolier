#ifndef BANDOLIER_OPEN_GL_TEXTURE_1_D_HH
#define BANDOLIER_OPEN_GL_TEXTURE_1_D_HH

#include <texture.hh>

#include <vector>

namespace Bandolier {

class OpenGLTexture1D : public Texture1D {
private:
  std::string mPath;
  uint32_t mLength;
  uint32_t mID;

public:
  void Bind(uint32_t slot) const override;

  [[nodiscard]]
  std::array<uint32_t, 3> Dims() const override;

  explicit OpenGLTexture1D(const std::vector<unsigned char>& path, unsigned int channels);

  virtual ~OpenGLTexture1D();
};

}

#endif //BANDOLIER_OPEN_GL_TEXTURE_2_D_HH
