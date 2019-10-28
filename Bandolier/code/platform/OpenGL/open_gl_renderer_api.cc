#include <glad/glad.h>

#include "open_gl_renderer_api.hh"

namespace Bandolier {

void
OpenGlRendererAPI::Init()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void
OpenGlRendererAPI::SetClearColor(const glm::vec4& color)
{
  glClearColor(color.r, color.g, color.b, color.a);
}

void
OpenGlRendererAPI::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
OpenGlRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& VAO)
{
  glDrawElements(GL_TRIANGLES, VAO->GetIndexBuffer()->Count(), GL_UNSIGNED_INT, nullptr);
}

}
