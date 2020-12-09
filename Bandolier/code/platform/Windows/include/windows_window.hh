#ifndef TEST_WINDOWS_WINDOW_HH
#define TEST_WINDOWS_WINDOW_HH

#include <string>

#include "GraphicsContext.hh"
#include "Window.hh"

struct GLFWwindow;

namespace Bandolier {

class WindowsWindow : public Window {
private:
  GLFWwindow* mWindow;
  std::unique_ptr<GraphicsContext> mContext;

  inline static bool sGLFWInitialized = false;

public:
  explicit
  WindowsWindow(WindowProperties props);

  virtual ~WindowsWindow();

  void OnUpdate() override;

  [[nodiscard]]
  inline unsigned int Width() const override {
    return mData.width;
  }

  [[nodiscard]]
  inline unsigned int Height() const override {
    return mData.height;
  }

  [[nodiscard]]
  bool VSync() const override;

  void VSync(bool enabled) override;

  [[nodiscard]]
  void* Native() override;
};

}

#endif //TEST_WINDOWS_WINDOW_HH
