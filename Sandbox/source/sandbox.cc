#include <iostream>

#include <glad/glad.h>

#include <entrypoint.hh>
#include <logger.hh>
#include <ApplicationEvent.hh>
#include <imgui/imgui_layer.hh>
#include <Renderer/buffer.hh>

#include "sandbox.hh"

using WindowResizeEvent = Bandolier::Events::WindowResize;

GLenum ShaderDataTypeToOpenGLBase(Bandolier::ShaderDataType type)
{
  switch(type)
  {
  case Bandolier::ShaderDataType::Float:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Float2:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Float3:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Float4:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Mat2:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Mat3:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Mat4:
    return GL_FLOAT;
  case Bandolier::ShaderDataType::Int:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Int2:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Int3:
    [[fallthrough]];
  case Bandolier::ShaderDataType::Int4:
    return GL_INT;
  case Bandolier::ShaderDataType::Bool:
    return GL_BOOL;
  }

  Bandolier::logging::client()->error("Unrecognized shader data type!");
  return GL_NONE;
}

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

  glGenVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);

  float vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
     0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
  };
  unsigned int indices[] = {
    0, 1, 2,
  };

  mVBO = Bandolier::VertexBuffer::create(vertices, sizeof(vertices));
  mIBO = Bandolier::IndexBuffer::create(indices, sizeof(indices) / sizeof(decltype(indices[0])));

  {
    Bandolier::BufferLayout layout = {
      {Bandolier::ShaderDataType::Float3, "a_Position"},
      {Bandolier::ShaderDataType::Float4, "a_Color"},
    };

    mVBO->Layout() = layout;
  }

  uint32_t index = 0;
  const auto& layout = mVBO->Layout();
  for(const auto& element : layout)
  {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(
            index,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGLBase(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE,
            layout.Stride(),
            (const void*)element.Offset);
    ++index;
  }

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

  mShader = std::make_unique<Bandolier::Shader>(vertexSource, fragmentSource);
}

void Sandbox::run()
{
  glClearColor(0.1f, 0.1f, 0.1f, 1);

  mRunning = true;
  while(mRunning)
  {
    mWindow->OnUpdate();
    glClear(GL_COLOR_BUFFER_BIT);

    mShader->Bind();
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

