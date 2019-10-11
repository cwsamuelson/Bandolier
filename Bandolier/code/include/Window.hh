#ifndef TEST_WINDO_HH
#define TEST_WINDO_HH

#include <string>

#include <event_handler.hh>

#include "events.hh"
#include "KeyEvent.hh"
#include "MouseEvents.hh"
#include "ApplicationEvent.hh"

namespace Bandolier {

struct WindowProperties
{
  template<typename T>
  using trigger_t = gsw::event_trigger<const T&>;

  std::string title;
  unsigned int width;
  unsigned int height;
  bool vsync;
  trigger_t<Events::BaseEvent> allEventsTrigger;
  trigger_t<Events::ApplicationEvent> appTrigger;
  trigger_t<Events::KeyEvent> keyTrigger;
  trigger_t<Events::MouseEvent> mouseTrigger;
  trigger_t<Events::MouseButtonEvent> mouseButtonTrigger;
  trigger_t<Events::WindowEvent> windowTrigger;
  trigger_t<Events::WindowResize> resizeTrigger;
  trigger_t<Events::WindowClose> closeTrigger;
  trigger_t<Events::WindowGainedFocus> windowGainFocusTrigger;
  trigger_t<Events::WindowLostFocus> windowLostFocusTrigger;
  trigger_t<Events::KeyTyped> keyTypedTrigger;
  trigger_t<Events::KeyPressed> keyPressTrigger;
  trigger_t<Events::KeyReleased> keyReleaseTrigger;
  trigger_t<Events::MouseButtonPressed> mouseButtonPressTrigger;
  trigger_t<Events::MouseButtonReleased> mouseButtonReleaseTrigger;
  trigger_t<Events::MouseScrolled> mouseScrollTrigger;
  trigger_t<Events::MouseMoved> mouseMoveTrigger;

  WindowProperties(std::string intitle, unsigned int inwidth, unsigned int inheight, bool invsync = true)
    : title(std::move(intitle))
    , width(inwidth)
    , height(inheight)
    , vsync(invsync)
  {}
};

class Window
{
public:
  virtual ~Window() = default;

  virtual void
  OnUpdate() = 0;

  virtual unsigned int
  Width() const = 0;
  virtual unsigned int
  Height() const = 0;

  virtual bool
  VSync() const = 0;
  virtual void
  VSync(bool enabled) = 0;

  virtual void*
  Native() = 0;

  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::allEventsTrigger)::channel_t>
  AllChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::appTrigger)::channel_t>
  AppChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::keyTrigger)::channel_t>
  KeyChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::mouseTrigger)::channel_t>
  MouseChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::mouseButtonTrigger)::channel_t>
  MouseButtonChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::resizeTrigger)::channel_t>
  ResizeChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::closeTrigger)::channel_t>
  CloseChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::keyTypedTrigger)::channel_t>
  KeyTypedChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::keyPressTrigger)::channel_t>
  KeyPressChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::keyReleaseTrigger)::channel_t>
  KeyReleaseChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::mouseButtonPressTrigger)::channel_t>
  MousePressChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::mouseButtonReleaseTrigger)::channel_t>
  MouseReleaseChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::mouseScrollTrigger)::channel_t>
  MouseScrollChannel() const = 0;
  [[nodiscard]]
  virtual
  std::weak_ptr<decltype(WindowProperties::mouseMoveTrigger)::channel_t>
  MouseMoveChannel() const = 0;
};

}

#endif //TEST_WINDO_HH
