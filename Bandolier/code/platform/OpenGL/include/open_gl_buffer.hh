#ifndef BANDOLIER_OPEN_GL_BUFFER_HH
#define BANDOLIER_OPEN_GL_BUFFER_HH

#include "buffer.hh"

namespace Bandolier {

class OpenGlVertexBuffer : public VertexBuffer
{
private:
  uint32_t mID;
  BufferLayout mLayout;

public:
  OpenGlVertexBuffer(const float* vertices, uint32_t size);
  virtual ~OpenGlVertexBuffer();

  void
  Bind() const override;
  void
  Unbind() const override;

  const BufferLayout&
  Layout() const override
  {
    return mLayout;
  }

  BufferLayout&
  Layout() override
  {
    return mLayout;
  }
};

class OpenGlIndexBuffer : public IndexBuffer
{
private:
  uint32_t mID;
  uint32_t mCount;

public:
  OpenGlIndexBuffer(const uint32_t* indices, uint32_t count);
  virtual ~OpenGlIndexBuffer();

  void
  Bind() const override;
  void
  Unbind() const override;

  uint32_t
  Count() const override
  {
    return mCount;
  }
};

}

#endif //BANDOLIER_OPEN_GL_BUFFER_HH
