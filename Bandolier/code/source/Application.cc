#include <GLFW/glfw3.h>

#include "platform/Windows/windows_window.hh"
#include "logger.hh"

#include "Application.hh"

namespace Bandolier{

Application::Application(std::string WindowName, std::tuple<unsigned int, unsigned int> dims)
  : mWindow(std::make_unique<WindowsWindow>(WindowProperties(std::move(WindowName), std::get<0>(dims), std::get<1>(dims))))
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

}
