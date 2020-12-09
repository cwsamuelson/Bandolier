#include <open_gl_texture_1_d.hh>
#include <open_gl_texture_2_d.hh>
#include <errors.hh>
#include "texture.hh"
#include "renderer_api.hh"

namespace Bandolier {

std::shared_ptr<Texture1D> Texture1D::Create(const std::vector<unsigned char>& path, unsigned int channels) {
  switch(RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    BNDLR_FAIL("A rendering API must be chosen!");
  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGLTexture1D>(path, channels);
  case RendererAPI::API::Vulkan:
    BNDLR_FAIL("Vulkan is not supported");
  case RendererAPI::API::Direct3D:
    BNDLR_FAIL("Direct3D is not supported");
  }
}

std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path) {
  switch(RendererAPI::GetAPI()) {
  case RendererAPI::API::None:
    BNDLR_FAIL("A rendering API must be chosen!");
  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGLTexture2D>(path);
  case RendererAPI::API::Vulkan:
    BNDLR_FAIL("Vulkan is not supported");
  case RendererAPI::API::Direct3D:
    BNDLR_FAIL("Direct3D is not supported");
  }
}

}