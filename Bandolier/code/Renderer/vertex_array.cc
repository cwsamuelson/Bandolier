#include "vertex_array.hh"
#include "renderer.hh"

#include "platform/OpenGL/open_gl_vertex_array.hh"

namespace Bandolier{

std::unique_ptr<VertexArray>
VertexArray::create()
{
  switch(Renderer::GetAPI())
  {
  case Renderer::API::None:
    logging::core()->error("Rendering API must be specified!");
    return nullptr;

  case Renderer::API::OpenGL:
    return std::make_unique<OpenGlVertexArray>();

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
