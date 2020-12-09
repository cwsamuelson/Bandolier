#ifndef BANDOLIER_OPEN_GL_TEXTURE_2_D_HH
#define BANDOLIER_OPEN_GL_TEXTURE_2_D_HH

#include <texture.hh>

namespace Bandolier {

class OpenGLTexture2D : public Texture2D {
private:
  std::string mPath;
  uint32_t mWidth;
  uint32_t mHeight;
  uint32_t mID;

public:
  [[nodiscard]]
  std::array<uint32_t, 3> Dims() const override;

  void Bind(uint32_t slot) const override;

  explicit OpenGLTexture2D(std::string path);
  virtual ~OpenGLTexture2D();
};

}

#endif //BANDOLIER_OPEN_GL_TEXTURE_2_D_HH
