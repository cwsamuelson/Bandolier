#include <iostream>

#include <Renderer/render_command.hh>
#include <Renderer/renderer.hh>
#include <entrypoint.hh>
#include <logger.hh>
#include <ApplicationEvent.hh>
#include <imgui/imgui_layer.hh>
#include <Renderer/buffer.hh>

#include "sandbox.hh"

using WindowResizeEvent = Bandolier::Events::WindowResize;

Sandbox::Sandbox()
{
  Window().AllChannel().lock()->subscribe(
    [this](const Bandolier::Events::BaseEvent& e)
    {
      for(auto it = mLayerStack.rbegin(); it != mLayerStack.rend(); ++it)
      {
        if((*it)->OnEvent(e))
        {
          break;
        }
      }
    }
  );

  //example layer?...crap!
  PushOverlay(std::make_shared<Bandolier::ImguiLayer>());

  float vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
     0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
  };
  unsigned int indices[] = {
    0, 1, 2,
  };

  mVAO = Bandolier::VertexArray::create();
  auto VBO = Bandolier::VertexBuffer::create(vertices, sizeof(vertices));
  auto IBO = Bandolier::IndexBuffer::create(indices, sizeof(indices) / sizeof(decltype(indices[0])));

  {
    Bandolier::BufferLayout layout = {
      {Bandolier::ShaderDataType::Float3, "a_Position"},
      {Bandolier::ShaderDataType::Float4, "a_Color"},
    };

    VBO->Layout() = layout;
    mVAO->AddVertexBuffer(VBO);
  }
  mVAO->SetIndexBuffer(IBO);

  float squareVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
  };
  uint32_t squareIndices[] = {
    0, 1, 2, 2, 3, 0
  };

  mSquareVAO = Bandolier::VertexArray::create();
  auto squareVB = Bandolier::VertexBuffer::create(squareVertices, sizeof(squareVertices));
  auto squareIB = Bandolier::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0]));
  squareVB->Layout() = Bandolier::BufferLayout{
    {Bandolier::ShaderDataType::Float3, "a_Position"}
  };
  mSquareVAO->AddVertexBuffer(squareVB);
  mSquareVAO->SetIndexBuffer(squareIB);

  std::string vertexSource = R"glsl(
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

out vec3 v_Position;
out vec4 v_Color;

void main()
{
  v_Color = a_Color;
  v_Position = a_Position;
  gl_Position = vec4(a_Position, 1.0f);
}
)glsl";

  std::string fragmentSource = R"glsl(
#version 330 core

in vec3 v_Position;
in vec4 v_Color;

out vec4 color;

void main()
{
  color = v_Color;
}
)glsl";

  std::string colorVertexSource = R"glsl(
#version 330 core

layout(location = 0) in vec3 a_Position;

out vec3 v_Position;

void main()
{
  v_Position = a_Position;
  gl_Position = vec4(a_Position, 1.0);
}
)glsl";

  std::string colorFragmentSource = R"glsl(
#version 330 core

in vec3 v_Position;

out vec4 color;

void main()
{
  color = vec4(0.2, 0.3, 0.8, 1.0);
}
)glsl";

  mShader = std::make_unique<Bandolier::Shader>(vertexSource, fragmentSource);
  mColorShader = std::make_unique<Bandolier::Shader>(colorVertexSource, colorFragmentSource);
}

void Sandbox::run()
{
  Bandolier::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});

  mRunning = true;
  while(mRunning)
  {
    mWindow->OnUpdate();
    Bandolier::RenderCommand::Clear();

    Bandolier::Renderer::BeginScene();

    mColorShader->Bind();
    Bandolier::Renderer::Submit(mSquareVAO);

    mShader->Bind();
    Bandolier::Renderer::Submit(mVAO);

    Bandolier::Renderer::EndScene();

    for(auto& layer : mLayerStack)
    {
      layer->OnUpdate();
    }
  }
}

Bandolier::Application& Bandolier::CreateApplication()
{
  Application::Instance = new Sandbox;
  return Application::Get();
}

