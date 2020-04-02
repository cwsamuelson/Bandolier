#include <glad/glad.h>

#include "buffer.hh"

#include "open_gl_vertex_array.hh"

namespace Bandolier {

static GLenum
ShaderDataTypeToOpenGLBase(Bandolier::ShaderDataType type)
{
  switch(type)
  {
  case Bandolier::ShaderDataType::Float:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Float2:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Float3:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Float4:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Mat2:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Mat3:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Mat4:
    return GL_FLOAT;
  case Bandolier::ShaderDataType::Int:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Int2:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Int3:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Int4:
    return GL_INT;
  case Bandolier::ShaderDataType::Bool:
    return GL_BOOL;
  }

  Bandolier::logging::client()->error("Unrecognized shader data type!");
  return GL_NONE;
}

OpenGlVertexArray::OpenGlVertexArray()
{
  glCreateVertexArrays(1, &mID);
}

OpenGlVertexArray::~OpenGlVertexArray()
{
  glDeleteVertexArrays(1, &mID);
}

void
OpenGlVertexArray::Bind() const
{
  glBindVertexArray(mID);
}

void
OpenGlVertexArray::Unbind() const
{
  glBindVertexArray(0);
}

void
OpenGlVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VBO)
{
  glBindVertexArray(mID);
  VBO->Bind();

  const auto& layout = VBO->Layout();
  for(const auto& element : layout)
  {
    glEnableVertexAttribArray(mVBIndex);
    glVertexAttribPointer(
            mVBIndex,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGLBase(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE,
            layout.Stride(),
            (const void*)element.Offset);
    ++mVBIndex;
  }

  mVBOs.push_back(VBO);
}

void
OpenGlVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IBO)
{
  glBindVertexArray(mID);
  IBO->Bind();

  mIBO = IBO;
}

const std::vector<std::shared_ptr<Bandolier::VertexBuffer>>&
OpenGlVertexArray::GetVertexBuffers() const
{
  return mVBOs;
}

const std::shared_ptr<Bandolier::IndexBuffer>&
OpenGlVertexArray::GetIndexBuffer() const
{
  return mIBO;
}

}


