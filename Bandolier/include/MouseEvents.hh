#ifndef TEST_MOUSEEVENTS_HH
#define TEST_MOUSEEVENTS_HH

#include <events.hh>

namespace Bandolier::Events {

class MouseEvent : public BaseEvent
{
public:
  using Trigger_t = gsw::event_trigger<MouseEvent>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  virtual const char* Name() const {return "MouseEvent"; }

  EVENT_CATEGORY(EventCategory::Mouse | EventCategory::Input)
};

class MouseButtonEvent : public MouseEvent
{
public:
  using Trigger_t = gsw::event_trigger<MouseButtonEvent>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  inline int MouseButton() const
  {
    return mButton;
  }

protected:
  MouseButtonEvent(int button)
    : mButton(button)
  {}

  virtual const char* Name() const {return "MouseButtonEvent"; }

  int mButton;
};

class MouseButtonPressed : public MouseButtonEvent
{
public:
  using Trigger_t = gsw::event_trigger<MouseButtonPressed>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  MouseButtonPressed(int button)
    : MouseButtonEvent(button)
  {}

  virtual const char* Name() const {return "MouseButtonPressed"; }
};

class MouseButtonReleased : public MouseButtonEvent
{
public:
  using Trigger_t = gsw::event_trigger<MouseButtonReleased>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  MouseButtonReleased(int button)
          : MouseButtonEvent(button)
  {}

  virtual const char* Name() const {return "MouseButtonReleased"; }
};

class MouseMoved : public MouseEvent
{
public:
  using Trigger_t = gsw::event_trigger<MouseMoved>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  MouseMoved(float x, float y)
    : mX(x)
    , mY(y)
  {}

  virtual const char* Name() const {return "MouseMoved"; }

  inline float X() const
  {
    return mX;
  }

  inline float Y() const
  {
    return mY;
  }

  inline
  std::pair<float, float>
  position() const
  {
    return {mX, mY};
  }

private:
  float mX;
  float mY;
};

class MouseScrolled : public MouseEvent
{
public:
  using Trigger_t = gsw::event_trigger<MouseScrolled>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  MouseScrolled(float xOffset, float yOffset)
    : mXOffset(xOffset)
    , mYOffset(yOffset)
  {}

  virtual const char* Name() const {return "MouseScrolled"; }

  inline
  float
  XOffset() const
  {
    return mXOffset;
  }

  inline
  float
  YOffset() const
  {
    return mYOffset;
  }

  inline
  std::pair<float, float>
  Offset() const
  {
    return {mXOffset, mYOffset};
  }

private:
  float mXOffset;
  float mYOffset;
};

}

#endif //TEST_MOUSEEVENTS_HH
