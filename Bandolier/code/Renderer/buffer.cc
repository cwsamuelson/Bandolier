#include "logger.hh"
#include "platform/OpenGL/open_gl_buffer.hh"

#include "buffer.hh"
#include "renderer.hh"

namespace Bandolier{

std::shared_ptr<VertexBuffer>
VertexBuffer::create(const float* vertices, uint32_t size)
{
  switch(Renderer::GetAPI())
  {
  case Renderer::API::None:
    logging::core()->error("Rendering API must be specified!");
    return nullptr;

  case Renderer::API::OpenGL:
    return std::make_shared<OpenGlVertexBuffer>(vertices, size);

  case Renderer::API::Direct3D:
    logging::core()->error("Rendering API Direct3D is not supported!");
    break;

  case Renderer::API::Vulkan:
    logging::core()->error("Rendering API Vulkan is not supported!");
    break;

  default:
    logging::core()->error("Unknown rendering API");
    break;
  }

  return nullptr;
}

std::shared_ptr<VertexBuffer>
VertexBuffer::create(const std::vector<float>& indices)
{
  return VertexBuffer::create(indices.data(), indices.size());
}

std::shared_ptr<IndexBuffer>
IndexBuffer::create(const uint32_t* indices, uint32_t count)
{
  switch(Renderer::GetAPI())
  {
  case Renderer::API::None:
    logging::core()->error("Rendering API must be specified!");
    return nullptr;

  case Renderer::API::OpenGL:
    return std::make_shared<OpenGlIndexBuffer>(indices, count);

  case Renderer::API::Direct3D:
    logging::core()->error("Rendering API Direct3D is not supported!");
    break;

  case Renderer::API::Vulkan:
    logging::core()->error("Rendering API Vulkan is not supported!");
    break;

  default:
    logging::core()->error("Unknown rendering API");
    break;
  }

  return nullptr;
}

std::shared_ptr<IndexBuffer>
IndexBuffer::create(const std::vector<uint32_t>& indices)
{
  return IndexBuffer::create(indices.data(), indices.size());
}

}
