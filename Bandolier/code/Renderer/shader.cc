#include <vector>

#include <platform/OpenGL/open_gl_shader.hh>

#include "logger.hh"

#include "shader.hh"
#include "../../vendor/glm/glm/gtc/type_ptr.inl"
#include "renderer_api.hh"

namespace Bandolier {

std::shared_ptr<Shader>
Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
{
  switch(RendererAPI::GetAPI())
  {
  case RendererAPI::API::None:
    logging::core()->error("Rendering API must be specified!");
    return nullptr;

  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGlShader>(vertexSource, fragmentSource);

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

