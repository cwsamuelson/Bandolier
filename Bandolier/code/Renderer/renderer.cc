#include <platform/OpenGL/open_gl_shader.hh>
#include "renderer.hh"
#include "render_command.hh"

namespace Bandolier{

void
Renderer::BeginScene(OrthographicCamera& camera)
{
  sSceneData->ViewProjectionMatrix = camera.GetViewProjection();
}

void
Renderer::EndScene()
{
}

void
Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO, const glm::mat4& transform)
{
  auto oglShader = std::dynamic_pointer_cast<OpenGlShader>(shader);

  shader->Bind();
  oglShader->SetUniform("u_ViewProjection", sSceneData->ViewProjectionMatrix);
  oglShader->SetUniform("u_Transform", transform);

  VAO->Bind();
  RenderCommand::DrawIndexed(VAO);
}

void Renderer::SetViewport(uint32_t width, uint32_t height) {
  RenderCommand::SetViewport(width, height);
}

}

