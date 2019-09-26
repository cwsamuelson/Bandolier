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

  inline unsigned int
  Width() const override { return mData.width; }
  inline unsigned int
  Height() const override { return mData.height; }

  virtual bool
  VSync() const;
  virtual void
  VSync(bool enabled);

  std::weak_ptr<decltype(WindowProperties::allEventsTrigger)::channel_t>
  AllChannel() const override;
  std::weak_ptr<decltype(WindowProperties::appTrigger)::channel_t>
  AppChannel() const override;
  std::weak_ptr<decltype(WindowProperties::keyTrigger)::channel_t>
  KeyChannel() const override;
  std::weak_ptr<decltype(WindowProperties::mouseTrigger)::channel_t>
  MouseChannel() const override;
  std::weak_ptr<decltype(WindowProperties::mouseButtonTrigger)::channel_t>
  MouseButtonChannel() const override;
  std::weak_ptr<decltype(WindowProperties::resizeTrigger)::channel_t>
  ResizeChannel() const override;
  std::weak_ptr<decltype(WindowProperties::closeTrigger)::channel_t>
  CloseChannel() const override;
  std::weak_ptr<decltype(WindowProperties::keyPressTrigger)::channel_t>
  KeyPressChannel() const override;
  std::weak_ptr<decltype(WindowProperties::keyReleaseTrigger)::channel_t>
  KeyReleaseChannel() const override;
  std::weak_ptr<decltype(WindowProperties::mouseButtonPressTrigger)::channel_t>
  MousePressChannel() const override;
  std::weak_ptr<decltype(WindowProperties::mouseButtonReleaseTrigger)::channel_t>
  MouseReleaseChannel() const override;
  std::weak_ptr<decltype(WindowProperties::mouseScrollTrigger)::channel_t>
  MouseScrollChannel() const override;
  std::weak_ptr<decltype(WindowProperties::mouseMoveTrigger)::channel_t>
  MouseMoveChannel() const override;
};

}

#endif //TEST_WINDOWS_WINDOW_HH
