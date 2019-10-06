#include <iostream>

#include <glad/glad.h>

#include <entrypoint.hh>
#include <logger.hh>
#include <ApplicationEvent.hh>
#include <imgui/imgui_layer.hh>

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

  glGenVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);

  glGenBuffers(1, &mVBO);
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);

  glGenBuffers(1, &mIBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
  };
  unsigned int indices[] = {
          0, 1, 2,
  };

  glBufferData(GL_ARRAY_BUFFER,         sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

  std::string vertexSource = R"glsl(
#version 330 core

layout(location = 0) in vec3 a_Position;

out vec3 v_Position;

void main()
{
  v_Position = a_Position;
  gl_Position = vec4(a_Position, 1.0f);
}
)glsl";

  std::string fragmentSource = R"glsl(
#version 330 core

in vec3 v_Position;

out vec4 color;

void main()
{
  color = vec4(v_Position * 0.5 + 0.5, 1.0);
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

