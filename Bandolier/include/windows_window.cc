#include "windows_window.hh"

namespace Bandolier{

WindowsWindow::WindowsWindow(const Bandolier::WindowProperties& props)
  : mData(props)
{
  if(!sGLFWInitialized)
  {
    int success = glfwInit();
    sGLFWInitialized = true;
  }

  mWindow = glfwCreateWindow(int(mData.width), int(mData.height), mData.title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(mWindow);
  glfwSetWindowUserPointer(mWindow, &mData);
}

WindowsWindow::~WindowsWindow()
{
  glfwDestroyWindow(mWindow);
}

void WindowsWindow::SetEventCallback(const Window::Handler_t& callback)
{
}

void WindowsWindow::OnUpdate()
{
  glfwPollEvents();
  glfwSwapBuffers(mWindow);
}

void WindowsWindow::VSync(bool enabled)
{
  if(enabled)
  {
    glfwSwapInterval(1);
  }
  else
  {
    glfwSwapInterval(1);
  }

  mData.vsync = enabled;
}

bool WindowsWindow::VSync() const
{
  return mData.vsync;
}

}
