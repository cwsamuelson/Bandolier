#ifndef TEST_WINDOWS_WINDOW_HH
#define TEST_WINDOWS_WINDOW_HH

#include <string>

#include "GraphicsContext.hh"
#include "Window.hh"

struct GLFWwindow;

namespace Bandolier {

class WindowsWindow : public Window {
private:
  WindowProperties mData;
  GLFWwindow* mWindow;
  std::unique_ptr<GraphicsContext> mContext;

  inline static bool sGLFWInitialized = false;

public:
  WindowsWindow(const WindowProperties& props);

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

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::allEventsTrigger)::channel_t> AllChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::appTrigger)::channel_t> AppChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::keyTrigger)::channel_t> KeyChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::mouseTrigger)::channel_t> MouseChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::mouseButtonTrigger)::channel_t> MouseButtonChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::resizeTrigger)::channel_t> ResizeChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::closeTrigger)::channel_t> CloseChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::keyTypedTrigger)::channel_t> KeyTypedChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::keyPressTrigger)::channel_t> KeyPressChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::keyReleaseTrigger)::channel_t> KeyReleaseChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::mouseButtonPressTrigger)::channel_t> MousePressChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::mouseButtonReleaseTrigger)::channel_t> MouseReleaseChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::mouseScrollTrigger)::channel_t> MouseScrollChannel() const override;

  [[nodiscard]]
  std::weak_ptr<decltype(WindowProperties::mouseMoveTrigger)::channel_t> MouseMoveChannel() const override;
};

}

#endif //TEST_WINDOWS_WINDOW_HH
