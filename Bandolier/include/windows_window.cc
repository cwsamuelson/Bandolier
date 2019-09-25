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
  glfwSetWindowUserPointer(mWindow, &mData);
  VSync(props.vsync);

  glfwSetWindowSizeCallback(mWindow,
    [](GLFWwindow* window, int width, int height)
    {
      WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);
      data.width = width;
      data.height = height;

      data.resizeTrigger.fire(Events::WindowResize(width, height));
    }
  );

  glfwSetWindowCloseCallback(mWindow,
    [](GLFWwindow* window)
    {
        WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

        data.closeTrigger.fire(Events::WindowClose())
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
           data.keyPressTrigger.fire(Events::KeyPressed(key, 0));
         }
           break;

         case GLFW_RELEASE:
         {
           data.keyReleaseTrigger.fire(Events::KeyReleased(key));
         }
           break;

         case GLFW_REPEAT:
         {
           data.keyPressTrigger.fire(Events::KeyPressed(key, 1));
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
        data.mouseButtonPressTrigger.fire(Events::MouseButtonPressed(button));
      }
        break;

      case GLFW_RELEASE:
      {
        data.mouseButtonReleaseTrigger.fire(Events::MouseButtonReleased(button));
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

      data.mouseScrollTrigger.fire(Events::MouseScrolled((float(xOffset)), float(yOffset)));
    }
  );

  glfwSetCursorPosCallback(mWindow,
     [](GLFWwindow* window, double xPos, double yPos)
     {
       WindowProperties& data = *(WindowProperties*)glfwGetWindowUserPointer(window);

       data.mouseMoveTrigger.fire(Events::MouseMoved((float(xPos)), float(yPos)));
     }
  );
}

WindowsWindow::~WindowsWindow()
{
  glfwDestroyWindow(mWindow);
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
