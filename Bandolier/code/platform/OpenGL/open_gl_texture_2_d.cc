#include "glad/glad.h"

#include "errors.hh"
#include "stb_image.h"
#include "open_gl_texture_2_d.hh"

namespace Bandolier{

OpenGLTexture2D::OpenGLTexture2D(std::string path)
  : mPath(std::move(path))
{
  int width;
  int height;
  int channels;
  stbi_set_flip_vertically_on_load(true);
  stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  BNDLR_ASSERT(data, "Failure to load image");
  //mWidth and mHeight are not passed directly to stbi_load because of type differences
  mWidth = width;
  mHeight = height;

  glCreateTextures(GL_TEXTURE_2D, 1, &mID);
  glTextureStorage2D(mID, 1, GL_RGB8, mWidth, mHeight);

  glTextureParameteri(mID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(mID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureSubImage2D(mID, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
  glDeleteTextures(1, &mID);
}

uint32_t
OpenGLTexture2D::Width() const
{
  return mWidth;
}

uint32_t
OpenGLTexture2D::Height() const
{
  return mHeight;
}

void
OpenGLTexture2D::Bind(uint32_t slot) const
{
  glBindTextureUnit(slot, mID);
}

}