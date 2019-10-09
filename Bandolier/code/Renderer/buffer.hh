#ifndef BANDOLIER_BUFFER_HH
#define BANDOLIER_BUFFER_HH

#include <memory>
#include <vector>

namespace Bandolier{

enum class ShaderDataType
{
  None = 0,
  Float,
  Float2,
  Float3,
  Float4,
  Mat2,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool,
  Float1 = Float,
  Int1 = Int,
};

class VertexBuffer
{
public:
  virtual ~VertexBuffer() = default;

  virtual void
  Bind() const = 0;
  virtual void
  Unbind() const = 0;

  static std::unique_ptr<VertexBuffer>
  create(const float* vertices, uint32_t size);
  static std::unique_ptr<VertexBuffer>
  create(const std::vector<float>& indices);
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
  create(const float* indices, uint32_t count);
  static std::unique_ptr<IndexBuffer>
  create(const std::vector<float>& indices);
};

}

#endif //BANDOLIER_BUFFER_HH

