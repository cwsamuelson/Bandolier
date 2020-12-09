#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <errors.hh>

#include "logger.hh"
#include "KeyEvent.hh"
#include "MouseEvents.hh"
#include "open_gl_context.hh"

#include "windows_window.hh"

namespace Bandolier {

void WindowErrorHandler(int error_code, const char* description) {
  logging::core()->error("GLFW error ({0}): {1}", error_code, description);
}

WindowsWindow::WindowsWindow(Bandolier::WindowProperties props)
        : Window(std::move(props)){
  //! @NOTE this may be problematic when multithreaded
  if(!sGLFWInitialized) {
    VERIFY_AND_LOG(glfwInit(), "GLFW failed to initialize");
    sGLFWInitialized = true;
    glfwSetErrorCallback(WindowErrorHandler);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  mWindow = glfwCreateWindow(int(mData.width), int(mData.height), mData.title.c_str(), nullptr, nullptr);
  //! @TODO error handling/check the window
  VERIFY_AND_LOG(mWindow != nullptr, "GLFW failed to create {} window", mData.title);
  mContext = std::make_unique<OpenGLContext>(mWindow);

  glfwSetWindowUserPointer(mWindow, &mData);
  VSync(props.vsync);

  glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
    {
      WindowProperties& data = *(WindowProperties*) glfwGetWindowUserPointer(window);
      data.width = width;
      data.height = height;

      auto event = Events::WindowResize(width, height);
      data.resizeTrigger.fire(event);
      data.windowTrigger.fire(event);
      data.appTrigger.fire(event);
      data.allEventsTrigger.fire(event);
    });

  glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
    {
      WindowProperties& data = *(WindowProperties*) glfwGetWindowUserPointer(window);

      auto event = Events::WindowClose();
      data.closeTrigger.fire(event);
      data.windowTrigger.fire(event);
      data.appTrigger.fire(event);
      data.allEventsTrigger.fire(event);
    });

  glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      WindowProperties& data = *(WindowProperties*) glfwGetWindowUserPointer(window);

      switch(action) {
      case GLFW_PRESS: {
        auto event = Events::KeyPressed(key, 0);
        data.keyPressTrigger.fire(event);
        data.keyTrigger.fire(event);
        data.allEventsTrigger.fire(event);
      }
        break;

      case GLFW_RELEASE: {
        auto event = Events::KeyReleased(key);
        data.keyReleaseTrigger.fire(event);
        data.keyTrigger.fire(event);
        data.allEventsTrigger.fire(event);
      }
        break;

      case GLFW_REPEAT: {
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
    });

  glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
    {
      WindowProperties& data = *(WindowProperties*) glfwGetWindowUserPointer(window);

      switch(action) {
      case GLFW_PRESS: {
        auto event = Events::MouseButtonPressed(button);
        data.mouseButtonPressTrigger.fire(event);
        data.mouseButtonTrigger.fire(event);
        data.mouseTrigger.fire(event);
        data.allEventsTrigger.fire(event);
      }
        break;

      case GLFW_RELEASE: {
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
    });

  glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
    {
      WindowProperties& data = *(WindowProperties*) glfwGetWindowUserPointer(window);

      auto event = Events::MouseScrolled((float(xOffset)), float(yOffset));
      data.mouseScrollTrigger.fire(event);
      data.mouseTrigger.fire(event);
      data.allEventsTrigger.fire(event);
    });

  glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
    {
      WindowProperties& data = *(WindowProperties*) glfwGetWindowUserPointer(window);

      auto event = Events::MouseMoved((float(xPos)), float(yPos));
      data.mouseMoveTrigger.fire(event);
      data.mouseTrigger.fire(event);
      data.allEventsTrigger.fire(event);
    });

  glfwSetWindowFocusCallback(mWindow, [](GLFWwindow* window, int hasFocus)
    {
      WindowProperties& data = *(WindowProperties*) glfwGetWindowUserPointer(window);

      if(hasFocus) {
        auto event = Events::WindowGainedFocus();
        data.windowGainFocusTrigger.fire(event);
        data.windowTrigger.fire(event);
        data.appTrigger.fire(event);
        data.allEventsTrigger.fire(event);
      } else {
        auto event = Events::WindowLostFocus();
        data.windowLostFocusTrigger.fire(event);
        data.windowTrigger.fire(event);
        data.appTrigger.fire(event);
        data.allEventsTrigger.fire(event);
      }
    });

  glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keycode)
    {
      WindowProperties& data = *(WindowProperties*) glfwGetWindowUserPointer(window);

      auto event = Events::KeyTyped(keycode);
      data.keyTypedTrigger.fire(event);
      data.keyTrigger.fire(event);
      data.allEventsTrigger.fire(event);
    });
}

WindowsWindow::~WindowsWindow() {
  glfwDestroyWindow(mWindow);
  glfwTerminate();//maybe shouldn't do this one, but eh for now
}

void WindowsWindow::OnUpdate() {
  glfwPollEvents();
  mContext->SwapBuffers();
}

void WindowsWindow::VSync(bool enabled) {
  if(enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }

  mData.vsync = enabled;
}

bool WindowsWindow::VSync() const {
  return mData.vsync;
}

void* WindowsWindow::Native() {
  return mWindow;
}

}
