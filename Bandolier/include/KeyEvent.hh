#ifndef TEST_KEYEVENT_HH
#define TEST_KEYEVENT_HH

#include <events.hh>

namespace Bandolier::Events {

class KeyEvent : public BaseEvent
{
public:
  using Trigger_t = gsw::event_trigger<KeyEvent>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  inline int KeyCode() const
  {
    return mKeyCode;
  }

  EVENT_CATEGORY(EventCategory::Keyboard | EventCategory::Input)
protected:
  KeyEvent(int keycode)
    : mKeyCode(keycode)
  {}

  virtual const char* Name() const {return "KeyEvent"; }

private:
  int mKeyCode;
};

class KeyPressed : public KeyEvent
{
public:
  using Trigger_t = gsw::event_trigger<KeyPressed>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  KeyPressed(int keycode, int repeatCount)
    : KeyEvent(keycode)
    , mRepeatCount(repeatCount)
  {}

  virtual const char* Name() const {return "KeyPressed"; }

  inline int RepeatCount() const
  {
    return mRepeatCount;
  }

private:
  int mRepeatCount;
};

class KeyReleased : public KeyEvent
{
public:
  using Trigger_t = gsw::event_trigger<KeyReleased>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  KeyReleased(int keycode)
    : KeyEvent(keycode)
  {}

  virtual const char* Name() const {return "KeyReleased"; }
};

}

#endif //TEST_KEYEVENT_HH
