#include <vector>

#include <open_gl_shader.hh>

#include "logger.hh"

#include "shader.hh"
#include "glm/gtc/type_ptr.inl"
#include "renderer_api.hh"

namespace Bandolier {

std::shared_ptr<Shader> Shader::Create(std::string name,
                                       const std::string& vertexSource,
                                       const std::string& fragmentSource) {
  switch(RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    logging::core()->error("Rendering API must be specified!");
    return nullptr;

  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGlShader>(name, vertexSource, fragmentSource);

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

std::shared_ptr<Shader> Shader::Create(const std::string& filePath) {
  switch(RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    logging::core()->error("Rendering API must be specified!");
    return nullptr;

  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGlShader>(filePath);

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

void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader) {
  Add(shader->Name(), shader);
}

void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader) {
  mShaders[name] = shader;
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filePath) {
  auto shader = Shader::Create(filePath);
  Add(shader);
  return shader;
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath) {
  auto shader = Shader::Create(filePath);
  Add(name, shader);
  return shader;
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name) {
  return mShaders.at(name);
}

bool ShaderLibrary::Exists(const std::string& name) {
  return mShaders.count(name) > 0;
}

}

