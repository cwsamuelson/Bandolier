#include <GLFW/glfw3.h>

#include "Renderer/render_command.hh"
#include "platform/Windows/windows_window.hh"
#include "logger.hh"

#include "Application.hh"

namespace Bandolier{

Application::Application(std::string WindowName, std::tuple<unsigned int, unsigned int> dims)
  : mWindow(std::make_unique<WindowsWindow>(WindowProperties(std::move(WindowName), std::get<0>(dims), std::get<1>(dims))))
  , mLastTime(float(glfwGetTime()))
  , mImguiLayer(std::make_shared<ImguiLayer>())
{
  if(Application::Instance)
  {
    logging::core()->error("Initializing a new application when one already exists!");
    throw std::runtime_error("Initializing a new application when one already exists!");
  }
  Application::Instance = this;

  mWindow->CloseChannel().lock()->subscribe(
    [this](const Events::WindowClose&)
    {
        mRunning = false;
        Bandolier::logging::client()->trace("Window close event occurred!");
    }
  );

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

  PushOverlay(mImguiLayer);
}

void
Application::PushLayer(LayerStack::value_type layer)
{
  mLayerStack.PushLayer(std::move(layer));
}

void
Application::PushOverlay(Bandolier::LayerStack::value_type overlay)
{
  mLayerStack.PushOverlay(std::move(overlay));
}

void
Application::run()
{
  mRunning = true;

  while(mRunning)
  {
    auto time = time_point(glfwGetTime());
    time_step timestep = time - mLastTime;
    mLastTime = time;

    Bandolier::RenderCommand::Clear();

    mImguiLayer->Begin();
    for(auto& layer : mLayerStack)
    {
      layer->OnUpdate(timestep);
    }
    mImguiLayer->End();

    mWindow->OnUpdate();
  }
}

}
