#ifndef BANDOLIER_OPEN_GL_VERTEX_ARRAY_HH
#define BANDOLIER_OPEN_GL_VERTEX_ARRAY_HH

#include "Renderer/vertex_array.hh"

namespace Bandolier{

class OpenGlVertexArray : public VertexArray
{
private:
  uint32_t mID;
  std::vector<std::shared_ptr<VertexBuffer>> mVBOs;
  std::shared_ptr<IndexBuffer> mIBO;

public:
  OpenGlVertexArray();
  ~OpenGlVertexArray();

  void
  Bind() const override;
  void
  Unbind() const override;

  void
  AddVertexBuffer(std::shared_ptr<VertexBuffer> VBO) override;
  void
  SetIndexBuffer(std::shared_ptr<IndexBuffer> IBO) override;

  const std::vector<std::shared_ptr<Bandolier::VertexBuffer>>&
  GetVertexBuffers() const override;
  const std::shared_ptr<Bandolier::IndexBuffer>&
  GetIndexBuffer() const override;
};

}

#endif //BANDOLIER_OPEN_GL_VERTEX_ARRAY_HH
