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

static uint32_t
ShaderDataTypeSize(ShaderDataType type)
{
  switch(type)
  {
  case ShaderDataType::Float:
    return 4;

  case ShaderDataType::Float2:
    return 4 * 2;

  case ShaderDataType::Float3:
    return 4 * 3;

  case ShaderDataType::Float4:
    return 4 * 4;

  case ShaderDataType::Mat3:
    return 4 * 3 * 3;

  case ShaderDataType::Mat4:
    return 4 * 4 * 4;

  case ShaderDataType::Int:
    return 4;

  case ShaderDataType::Int2:
    return 4 * 2;

  case ShaderDataType::Int3:
    return 4 * 3;

  case ShaderDataType::Int4:
    return 4 * 4;

  case ShaderDataType::Bool:
    return 1;
  }

  logging::core()->error("Unknown shader data type");//! @TODO throw?
  return 0;
}
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

