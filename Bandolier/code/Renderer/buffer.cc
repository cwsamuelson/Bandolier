#include "logger.hh"

#include "buffer.hh"
#include "renderer.hh"

namespace Bandolier{

std::unique_ptr<VertexBuffer>
VertexBuffer::create(float*vertices, uint32_t size)
{
  switch(Renderer::API())
  {
  case Renderer::API::None:
    logging::core()->error("Rendering API must be specified!");
    return nullptr;
  case Renderer::API::OpenGL:
    return std::make_unique<OpenGLVertexBuffer>(vertices, size);
    break;
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

}
