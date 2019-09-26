#include <glad/glad.h>

#include "logger.hh"
#include "KeyEvent.hh"
#include "MouseEvents.hh"

#include "windows_window.hh"

namespace Bandolier{

void
WindowErrorHandler(int error_code, const char* description)
{
  logging::core()->error("GLFW error ({0}): {1}", error_code, description);
}

WindowsWindow::WindowsWindow(const Bandolier::WindowProperties& props)
  : mData(props)
{
  if(!sGLFWInitialized)
  {
    int success = glfwInit();
    sGLFWInitialized = true;
    glfwSetErrorCallback(WindowErrorHandler);
  }

  mWindow = glfwCreateWindow(int(mData.width), int(mData.height), mData.title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(mWindow);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    logging::core()->error("Failed to initialize GLAD");
    throw std::runtime_error("Failed to initialize GLAD");
  }
  glfwSetWindowUserPointer(mWindow, &mData);
  VSync(props.vsync);

  glfwSetWindowSizeCallback(mWindow,
    [](GLFWwindow* window, int width, int height)
    {
      WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);
      data.width = width;
      data.height = height;

      auto event = Events::WindowResize(width, height);
      data.resizeTrigger.fire(event);
      data.appTrigger.fire(event);
      data.allEventsTrigger.fire(event);
    }
  );

  glfwSetWindowCloseCallback(mWindow,
    [](GLFWwindow* window)
    {
        WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

        auto event = Events::WindowClose();
        data.closeTrigger.fire(event);
        data.appTrigger.fire(event);
        data.allEventsTrigger.fire(event);
    }
  );

  glfwSetKeyCallback(mWindow,
     [](GLFWwindow* window, int key, int scancode, int action, int mods)
     {
         WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

         switch(action)
         {
         case GLFW_PRESS:
         {
           auto event = Events::KeyPressed(key, 0);
           data.keyPressTrigger.fire(event);
           data.keyTrigger.fire(event);
           data.allEventsTrigger.fire(event);
         }
           break;

         case GLFW_RELEASE:
         {
           auto event = Events::KeyReleased(key);
           data.keyReleaseTrigger.fire(event);
           data.keyTrigger.fire(event);
           data.allEventsTrigger.fire(event);
         }
           break;

         case GLFW_REPEAT:
         {
           auto event = Events::KeyPressed(key, 1);
           data.keyPressTrigger.fire(event);
           data.keyTrigger.fire(event);
           data.allEventsTrigger.fire(event);
         }
           break;

         default:
           //wat
           break;
         }
     }
  );

  glfwSetMouseButtonCallback(mWindow,
    [](GLFWwindow* window, int button, int action, int mods)
    {
      WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

      switch(action)
      {
      case GLFW_PRESS:
      {
        auto event = Events::MouseButtonPressed(button);
        data.mouseButtonPressTrigger.fire(event);
        data.mouseButtonTrigger.fire(event);
        data.mouseTrigger.fire(event);
        data.allEventsTrigger.fire(event);
      }
        break;

      case GLFW_RELEASE:
      {
        auto event = Events::MouseButtonReleased(button);
        data.mouseButtonReleaseTrigger.fire(event);
        data.mouseButtonTrigger.fire(event);
        data.mouseTrigger.fire(event);
        data.allEventsTrigger.fire(event);
      }
        break;

      default:
        //wat
        break;
      }
    }
  );

  glfwSetScrollCallback(mWindow,
    [](GLFWwindow* window, double xOffset, double yOffset)
    {
      WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

      auto event = Events::MouseScrolled((float(xOffset)), float(yOffset));
      data.mouseScrollTrigger.fire(event);
      data.mouseTrigger.fire(event);
      data.allEventsTrigger.fire(event);
    }
  );

  glfwSetCursorPosCallback(mWindow,
     [](GLFWwindow* window, double xPos, double yPos)
     {
       WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

       auto event = Events::MouseMoved((float(xPos)), float(yPos));
       data.mouseMoveTrigger.fire(event);
       data.mouseTrigger.fire(event);
       data.allEventsTrigger.fire(event);
     }
  );
}

WindowsWindow::~WindowsWindow()
{
  glfwDestroyWindow(mWindow);
}

std::weak_ptr<decltype(WindowProperties::allEventsTrigger)::channel_t>
WindowsWindow::AllChannel() const
{
  return mData.allEventsTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::appTrigger)::channel_t>
WindowsWindow::AppChannel() const
{
  return mData.appTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::keyTrigger)::channel_t>
WindowsWindow::KeyChannel() const
{
  return mData.keyTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::mouseTrigger)::channel_t>
WindowsWindow::MouseChannel() const
{
  return mData.mouseTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::mouseButtonTrigger)::channel_t>
WindowsWindow::MouseButtonChannel() const
{
  return mData.mouseButtonTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::resizeTrigger)::channel_t>
WindowsWindow::ResizeChannel() const
{
  return mData.resizeTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::closeTrigger)::channel_t>
WindowsWindow::CloseChannel() const
{
  return mData.closeTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::keyPressTrigger)::channel_t>
WindowsWindow::KeyPressChannel() const
{
  return mData.keyPressTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::keyReleaseTrigger)::channel_t>
WindowsWindow::KeyReleaseChannel() const
{
  return mData.keyReleaseTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::mouseButtonPressTrigger)::channel_t>
WindowsWindow::MousePressChannel() const
{
  return mData.mouseButtonPressTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::mouseButtonReleaseTrigger)::channel_t>
WindowsWindow::MouseReleaseChannel() const
{
  return mData.mouseButtonReleaseTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::mouseScrollTrigger)::channel_t>
WindowsWindow::MouseScrollChannel() const
{
  return mData.mouseScrollTrigger.getChannel();
}

std::weak_ptr<decltype(WindowProperties::mouseMoveTrigger)::channel_t>
WindowsWindow::MouseMoveChannel() const
{
  return mData.mouseMoveTrigger.getChannel();
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
    glfwSwapInterval(0);
  }

  mData.vsync = enabled;
}

bool WindowsWindow::VSync() const
{
  return mData.vsync;
}

}
