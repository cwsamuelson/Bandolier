#include "renderer.hh"
#include "render_command.hh"

namespace Bandolier{

void
Renderer::BeginScene()
{
}

void
Renderer::EndScene()
{
}

void
Renderer::Submit(std::shared_ptr <VertexArray> VAO)
{
  VAO->Bind();
  RenderCommand::DrawIndexed(VAO);
}

}

