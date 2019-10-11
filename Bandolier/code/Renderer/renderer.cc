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
Renderer::Submit(std::shared_ptr<Shader> shader, std::shared_ptr<VertexArray> VAO)
{
  shader->Bind();
  shader->UploaduniformMat4("u_ViewProjection", sSceneData->ViewProjectionMatrix);

  VAO->Bind();
  RenderCommand::DrawIndexed(VAO);
}

}

