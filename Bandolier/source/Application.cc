#include <GLFW/glfw3.h>

#include "windows_window.hh"

#include "Application.hh"

namespace Bandolier{

Application::Application()
  : mWindow(std::make_unique<WindowsWindow>(WindowProperties("test", 1280, 720)))
{
  mWindow->CloseChannel().lock()->subscribe(
    [this](const Events::WindowClose&)
    {
      mRunning = false;
    }
  );
}

Application::~Application()
{
}

}
