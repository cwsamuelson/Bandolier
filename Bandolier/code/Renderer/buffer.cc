#include "logger.hh"
#include "platform/OpenGL/open_gl_buffer.hh"
#include "Renderer/renderer_api.hh"

#include "buffer.hh"
#include "renderer.hh"
#include "renderer_api.hh"

namespace Bandolier{

std::shared_ptr<VertexBuffer>
VertexBuffer::create(const float* vertices, uint32_t size)
{
  switch(RendererAPI::GetAPI())
  {
  case RendererAPI::API::None:
    logging::core()->error("Rendering API must be specified!");
    return nullptr;

  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGlVertexBuffer>(vertices, size);

  case RendererAPI::API::Direct3D:
    logging::core()->error("Rendering API Direct3D is not supported!");
    break;

  case RendererAPI::API::Vulkan:
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
  switch(RendererAPI::GetAPI())
  {
  case RendererAPI::API::None:
    logging::core()->error("Rendering API must be specified!");
    return nullptr;

  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGlIndexBuffer>(indices, count);

  case RendererAPI::API::Direct3D:
    logging::core()->error("Rendering API Direct3D is not supported!");
    break;

  case RendererAPI::API::Vulkan:
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
