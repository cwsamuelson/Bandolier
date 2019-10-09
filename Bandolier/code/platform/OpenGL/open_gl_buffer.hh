#ifndef BANDOLIER_OPEN_GL_BUFFER_HH
#define BANDOLIER_OPEN_GL_BUFFER_HH

#include "Renderer/buffer.hh"

namespace Bandolier {

class OpenGlVertexBuffer : public VertexBuffer
{
private:
  uint32_t mID;
  BufferLayout mLayout;

public:
  OpenGlVertexBuffer(const float* vertices, uint32_t size);
  virtual ~OpenGlVertexBuffer();

  virtual void
  Bind() const override;
  virtual void
  Unbind() const override;

  virtual const BufferLayout&
  Layout() const override
  {
    return mLayout;
  }

  virtual BufferLayout&
  Layout() override
  {
    return mLayout;
  }
};

class OpenGlIndexBuffer : public IndexBuffer
{
public:
  OpenGlIndexBuffer(const float* indices, uint32_t count);
  virtual ~OpenGlIndexBuffer();

  virtual void
  Bind() const override;
  virtual void
  Unbind() const override;


  virtual uint32_t
  Count() const
  {
    return mCount;
  }
private:
  uint32_t mID;
  uint32_t mCount;
};

}

#endif //BANDOLIER_OPEN_GL_BUFFER_HH
