#ifndef BANDOLIER_BUFFER_HH
#define BANDOLIER_BUFFER_HH

#include <memory>

namespace Bandolier{

class VertexBuffer
{
public:
  virtual ~VertexBuffer() = default;

  virtual void
  Bind() const = 0;
  virtual void
  Unbind() const = 0;

  static std::unique_ptr<VertexBuffer>
  create(float* vertices, uint32_t size);
};

class IndexBuffer
{
public:
  virtual ~IndexBuffer() = default;

  virtual void
  Bind() const = 0;
  virtual void
  Unbind() const = 0;

  static std::unique_ptr<IndexBuffer>
  create(float* vertices, uint32_t size);
};

}

#endif //BANDOLIER_BUFFER_HH

