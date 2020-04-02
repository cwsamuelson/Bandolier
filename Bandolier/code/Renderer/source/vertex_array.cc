#include "vertex_array.hh"
#include "renderer.hh"

#include "open_gl_vertex_array.hh"

namespace Bandolier {

std::unique_ptr<VertexArray> VertexArray::Create() {
  switch(RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    logging::core()->error("Rendering API must be specified!");
    return nullptr;

  case RendererAPI::API::OpenGL:
    return std::make_unique<OpenGlVertexArray>();

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

}
