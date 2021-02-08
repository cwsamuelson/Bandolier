#include "sandbox_2_d.hh"

#include <vector>
#include <imgui.h>
#include <glm/ext.hpp>
#include <render_command.hh>
#include <renderer.hh>
#include <open_gl_shader.hh>

Sandbox2d::Sandbox2d()
  : Layer("Sandbox2D")
  , mCameraController(1280 / 720)
  , mSquare(Bandolier::VertexArray::Create())
  , mShader(Bandolier::Shader::Create("assets/shaders/FlatColor.glsl"))
  , mSquareColor(1.0f, 1.0f, 1.0f, 1.0f){

  std::vector<float> squareVertices {
          -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          0.5f,  0.5f, 0.0f,
          -0.5f,  0.5f, 0.0f
  };

  auto squareVB = Bandolier::VertexBuffer::create(squareVertices);
  squareVB->Layout() = Bandolier::BufferLayout{
          {Bandolier::ShaderDataType::Float3, "a_Position"}
  };

  std::vector<unsigned int> squareIndices{
    0, 1, 2, 2, 3, 0
  };
  auto squareIB = Bandolier::IndexBuffer::create(squareIndices);

  mSquare->AddVertexBuffer(squareVB);
  mSquare->SetIndexBuffer(squareIB);

  Bandolier::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
}

void Sandbox2d::OnUpdate(Bandolier::time_step ts) {
  mCameraController.OnUpdate(ts);

  OpenGLRender();
}

void Sandbox2d::OpenGLRender(){
  Bandolier::Renderer::BeginScene(mCameraController.Camera());

  auto ogl_shader = std::dynamic_pointer_cast<Bandolier::OpenGlShader>(mShader);

  ogl_shader->Bind();
  ogl_shader->SetUniform("u_Color", mSquareColor);

  Bandolier::Renderer::Submit(mShader, mSquare, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

  Bandolier::Renderer::EndScene();
}
