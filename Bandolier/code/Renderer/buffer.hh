#ifndef BANDOLIER_BUFFER_HH
#define BANDOLIER_BUFFER_HH

#include <memory>
#include <vector>

#include "logger.hh"

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

struct BufferElement
{
  std::string Name;
  ShaderDataType Type;
  uint32_t Size;
  uint32_t Offset;
  bool Normalized;

  BufferElement(ShaderDataType type, std::string name, bool normalized = false)
    : Name(std::move(name))
    , Type(type)
    , Size(ShaderDataTypeSize(type))
    , Offset(0)
    , Normalized(normalized)
  {}

  uint32_t
  GetComponentCount() const
  {
    switch(Type)
    {
    case ShaderDataType::Float:
      return 1;

    case ShaderDataType::Float2:
      return 2;

    case ShaderDataType::Float3:
      return 3;

    case ShaderDataType::Float4:
      return 4;

    case ShaderDataType::Mat3:
      return 3 * 3;

    case ShaderDataType::Mat4:
      return 4 * 4;

    case ShaderDataType::Int:
      return 1;

    case ShaderDataType::Int2:
      return 2;

    case ShaderDataType::Int3:
      return 3;

    case ShaderDataType::Int4:
      return 4;

    case ShaderDataType::Bool:
      return 1;
    }

    logging::core()->error("Unjnown shader data type!");//! @TODO throw?
    return 0;
  }
};

class BufferLayout
{
private:
  std::vector<BufferElement> mElements;
  uint32_t mStride = 0;

public:
  BufferLayout() = default;

  BufferLayout(const std::initializer_list<BufferElement>& elements)
    : mElements(elements)
  {
    CalculateOffsetAndStride();
  }

  inline uint32_t
  Stride() const
  {
    return mStride;
  }

  inline const std::vector<BufferElement>&
  Elements() const
  {
    return mElements;
  }

  auto
  begin()
  {
    return mElements.begin();
  }

  auto
  end()
  {
    return mElements.end();
  }

  auto
  begin() const
  {
    return mElements.begin();
  }

  auto
  end() const
  {
    return mElements.end();
  }

private:
  void
  CalculateOffsetAndStride()
  {
    uint32_t offset = 0;
    mStride = 0;
    for(auto& element : mElements)
    {
      element.Offset = offset;
      offset += element.Size;
      mStride += element.Size;
    }
  }
};

class VertexBuffer
{
public:
  virtual ~VertexBuffer() = default;

  virtual void
  Bind() const = 0;
  virtual void
  Unbind() const = 0;

  virtual const BufferLayout&
  Layout() const = 0;
  virtual BufferLayout&
  Layout() = 0;

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
  create(const uint32_t* indices, uint32_t count);
  static std::unique_ptr<IndexBuffer>
  create(const std::vector<uint32_t>& indices);
};

}

#endif //BANDOLIER_BUFFER_HH

