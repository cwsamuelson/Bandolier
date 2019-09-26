#include <iostream>

#include <glad/glad.h>

#include <entrypoint.hh>
#include <logger.hh>
#include <ApplicationEvent.hh>

#include "sandbox.hh"

using WindowResizeEvent = Bandolier::Events::WindowResize;

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

Bandolier::AppPtr Bandolier::CreateApplication()
{
  return std::make_unique<Sandbox>();
}

