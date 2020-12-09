#ifndef TEST_KEYEVENT_HH
#define TEST_KEYEVENT_HH

#include <event_handler.hh>

#include "events.hh"

namespace Bandolier::Events {

class KeyEvent : public BaseEvent {
public:
  using Trigger_t = gsw::event_trigger<void(KeyEvent)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  [[nodiscard]]
  inline int KeyCode() const {
    return mKeyCode;
  }

  EVENT_CATEGORY(EventCategory::Keyboard | EventCategory::Input)

  EVENT_TYPE(EventType::Key)

protected:
  explicit
  KeyEvent(unsigned int keycode)
          : mKeyCode(keycode) {
  }

  [[nodiscard]]
  const char* Name() const override {
    return "KeyEvent";
  }

private:
  unsigned int mKeyCode;
};

class KeyPressed : public KeyEvent {
public:
  using Trigger_t = gsw::event_trigger<void(KeyPressed)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  KeyPressed(int keycode, int repeatCount)
          : KeyEvent(keycode)
          , mRepeatCount(repeatCount) {
  }

  [[nodiscard]]
  const char* Name() const override {
    return "KeyPressed";
  }

  [[nodiscard]]
  inline int RepeatCount() const {
    return mRepeatCount;
  }

  EVENT_TYPE(EventType::KeyPressed)

private:
  int mRepeatCount;
};

class KeyReleased : public KeyEvent {
public:
  using Trigger_t = gsw::event_trigger<void(KeyReleased)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  explicit
  KeyReleased(int keycode)
          : KeyEvent(keycode) {
  }

  [[nodiscard]]
  const char* Name() const override {
    return "KeyReleased";
  }

  EVENT_TYPE(EventType::KeyReleased)
};

class KeyTyped : public KeyEvent {
public:
  using Trigger_t = gsw::event_trigger<void(KeyReleased)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  explicit
  KeyTyped(unsigned int keycode)
          : KeyEvent(keycode) {
  }

  EVENT_TYPE(EventType::KeyTyped)
};

}

#endif //TEST_KEYEVENT_HH
