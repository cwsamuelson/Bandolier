#ifndef TEST_WINDOWS_WINDOW_HH
#define TEST_WINDOWS_WINDOW_HH

#include <string>

#include "Windo.hh"

#include <GLFW/glfw3.h>

namespace Bandolier {

class WindowsWindow : public Window
{
private:
  WindowProperties mData;
  GLFWwindow* mWindow;

  inline static bool sGLFWInitialized = false;

public:
  WindowsWindow(const WindowProperties& props);

  virtual ~WindowsWindow();

  void OnUpdate() override;

  inline unsigned int Width() const override { return mData.width; }
  inline unsigned int Height() const override { return mData.height; }

  virtual bool VSync() const;
  virtual void VSync(bool enabled);

  virtual void SetEventCallback(const Window::Handler_t& callback);
};

}

#endif //TEST_WINDOWS_WINDOW_HH
