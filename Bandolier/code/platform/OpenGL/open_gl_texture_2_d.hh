#ifndef BANDOLIER_OPEN_GL_TEXTURE_2_D_HH
#define BANDOLIER_OPEN_GL_TEXTURE_2_D_HH

#include <Renderer/texture.hh>

namespace Bandolier {

class OpenGLTexture2D : public Texture2D
{
private:
  std::string mPath;
  uint32_t mWidth;
  uint32_t mHeight;
  uint32_t mID;

public:
  explicit
  OpenGLTexture2D(std::string path);
  virtual ~OpenGLTexture2D();

  uint32_t
  Width() const override;

  uint32_t
  Height() const override;

  void
  Bind(uint32_t slot) const override;
};

}

#endif //BANDOLIER_OPEN_GL_TEXTURE_2_D_HH
