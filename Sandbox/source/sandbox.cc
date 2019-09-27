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
  //example layer?...crap!
  PushOverlay(std::make_shared<Bandolier::ImguiLayer>());
}

void Sandbox::run()
{
  mRunning = true;
  while(mRunning)
  {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    mWindow->OnUpdate();

    for(auto& layer : mLayerStack)
    {
      layer->OnUpdate();
    }
  }
}

Bandolier::Application& Bandolier::CreateApplication()
{
  Application::AppInstance = new Sandbox;
  return Application::GetApplication();
}

