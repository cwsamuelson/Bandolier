#ifndef TEST_WINDO_HH
#define TEST_WINDO_HH

#include <string>

#include <event_handler.hh>
#include <utility>

#include "events.hh"
#include "KeyEvent.hh"
#include "MouseEvents.hh"
#include "ApplicationEvent.hh"

namespace Bandolier {

struct WindowProperties {
  template<typename T> using trigger_t = gsw::event_trigger<void(const T&)>;

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
          , vsync(invsync) {
  }
};

class Window {
protected:
  WindowProperties mData;

public:
  explicit
  Window(WindowProperties  props)
    : mData(std::move(props))
    , AllChannel(*mData.allEventsTrigger.getChannel().lock())
    , AppChannel(*mData.appTrigger.getChannel().lock())
    , KeyChannel(*mData.keyTrigger.getChannel().lock())
    , MouseChannel(*mData.mouseTrigger.getChannel().lock())
    , MouseButtonChannel(*mData.mouseButtonTrigger.getChannel().lock())
    , MousePressChannel(*mData.mouseButtonPressTrigger.getChannel().lock())
    , MouseReleaseChannel(*mData.mouseButtonReleaseTrigger.getChannel().lock())
    , MouseScrollChannel(*mData.mouseScrollTrigger.getChannel().lock())
    , MouseMoveChannel(*mData.mouseMoveTrigger.getChannel().lock())
    , WindowChannel(*mData.windowTrigger.getChannel().lock())
    , ResizeChannel(*mData.resizeTrigger.getChannel().lock())
    , CloseChannel(*mData.closeTrigger.getChannel().lock())
    , GainFocusChannel(*mData.windowGainFocusTrigger.getChannel().lock())
    , LostFocusChannel(*mData.windowLostFocusTrigger.getChannel().lock())
    , KeyTypedChannel(*mData.keyTypedTrigger.getChannel().lock())
    , KeyPressChannel(*mData.keyPressTrigger.getChannel().lock())
    , KeyReleaseChannel(*mData.keyReleaseTrigger.getChannel().lock())
  {}

  virtual ~Window() = default;

  virtual void OnUpdate() = 0;

  [[nodiscard]]
  virtual unsigned int Width() const = 0;

  [[nodiscard]]
  virtual unsigned int Height() const = 0;

  [[nodiscard]]
  virtual bool VSync() const = 0;

  virtual void VSync(bool enabled) = 0;

  virtual void* Native() = 0;

  decltype(WindowProperties::allEventsTrigger)::channel_t& AllChannel;
  decltype(WindowProperties::appTrigger)::channel_t& AppChannel;
  decltype(WindowProperties::keyTrigger)::channel_t& KeyChannel;
  decltype(WindowProperties::mouseTrigger)::channel_t& MouseChannel;
  decltype(WindowProperties::mouseButtonTrigger)::channel_t& MouseButtonChannel;
  decltype(WindowProperties::mouseButtonPressTrigger)::channel_t& MousePressChannel;
  decltype(WindowProperties::mouseButtonReleaseTrigger)::channel_t& MouseReleaseChannel;
  decltype(WindowProperties::mouseScrollTrigger)::channel_t& MouseScrollChannel;
  decltype(WindowProperties::mouseMoveTrigger)::channel_t& MouseMoveChannel;
  decltype(WindowProperties::windowTrigger)::channel_t& WindowChannel;
  decltype(WindowProperties::resizeTrigger)::channel_t& ResizeChannel;
  decltype(WindowProperties::closeTrigger)::channel_t& CloseChannel;
  decltype(WindowProperties::windowGainFocusTrigger)::channel_t& GainFocusChannel;
  decltype(WindowProperties::windowLostFocusTrigger)::channel_t& LostFocusChannel;
  decltype(WindowProperties::keyTypedTrigger)::channel_t& KeyTypedChannel;
  decltype(WindowProperties::keyPressTrigger)::channel_t& KeyPressChannel;
  decltype(WindowProperties::keyReleaseTrigger)::channel_t& KeyReleaseChannel;
};

}

#endif //TEST_WINDO_HH
