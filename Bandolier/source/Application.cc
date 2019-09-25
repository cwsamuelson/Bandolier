#include <GLFW/glfw3.h>

#include "windows_window.hh"
#include "logger.hh"

#include "Application.hh"

namespace Bandolier{

Application::Application()
  : mWindow(std::make_unique<WindowsWindow>(WindowProperties("test", 1280, 720)))
{
  mWindow->CloseChannel().lock()->subscribe(
    [this](const Events::WindowClose&)
    {
      mRunning = false;
      Bandolier::logging::client()->warn("Window close event happened!");
    }
  );
}

Application::~Application()
{
}

}
