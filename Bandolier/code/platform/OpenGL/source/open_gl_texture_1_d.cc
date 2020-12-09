#include "glad/glad.h"

#include "errors.hh"
#include "open_gl_texture_1_d.hh"

namespace Bandolier {

//implement for 1D
// probably don't actually want a path
// probably want an array/vector of colors
OpenGLTexture1D::OpenGLTexture1D(const std::vector<unsigned char>& data, unsigned int channels)
  : mLength(data.size()/channels){
  BNDLR_ASSERT(!data.empty(), "No data provided to texture");

  GLenum internalFormat = 0;
  GLenum dataFormat = 0;

  if(channels == 4) {
    internalFormat = GL_RGBA8;
    dataFormat = GL_RGBA;
  } else if(channels == 3) {
    internalFormat = GL_RGB8;
    dataFormat = GL_RGB;
  } else {
    BNDLR_FAIL("Invalid number of channels specified({}); only 3 or 4 channels are supported", channels);
  }

  glCreateTextures(GL_TEXTURE_1D, 1, &mID);
  glTextureStorage1D(mID, 1, internalFormat, mLength);

  glTextureParameteri(mID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(mID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureSubImage1D(mID, 0, 0, mLength, dataFormat, GL_UNSIGNED_BYTE, data.data());
}

OpenGLTexture1D::~OpenGLTexture1D() {
  glDeleteTextures(1, &mID);
}

void OpenGLTexture1D::Bind(uint32_t slot) const {
  glBindTextureUnit(slot, mID);
}

std::array<uint32_t, 3> OpenGLTexture1D::Dims() const {
  return {mLength, 1, 1};
}

}