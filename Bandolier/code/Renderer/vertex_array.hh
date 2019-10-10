#ifndef BANDOLIER_VERTEX_ARRAY_HH
#define BANDOLIER_VERTEX_ARRAY_HH

#include <memory>

#include "Renderer/buffer.hh"

namespace Bandolier {

class VertexArray
{
public:
  virtual ~VertexArray() = default;

  virtual void
  Bind() const = 0;
  virtual void
  Unbind() const = 0;

  virtual void
  AddVertexBuffer(std::shared_ptr<VertexBuffer> VBO) = 0;
  virtual void
  SetIndexBuffer(std::shared_ptr<IndexBuffer> IBO) = 0;

  virtual const std::vector<std::shared_ptr<Bandolier::VertexBuffer>>&
  GetVertexBuffers() const = 0;
  virtual const std::shared_ptr<Bandolier::IndexBuffer>&
  GetIndexBuffer() const = 0;

  static std::unique_ptr<VertexArray>
  create();
};

}

#endif //BANDOLIER_VERTEX_ARRAY_HH
