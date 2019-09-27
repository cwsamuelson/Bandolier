#ifndef TEST_APPLICATIONEVENT_HH
#define TEST_APPLICATIONEVENT_HH

#include <events.hh>

namespace Bandolier::Events {

class ApplicationEvent : public BaseEvent
{
public:
  using Trigger_t = gsw::event_trigger<ApplicationEvent>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  virtual const char* Name() const {return "ApplicationEvent"; }

  EVENT_CATEGORY(EventCategory::Application)
  EVENT_TYPE(EventType::App)
};

class WindowEvent : public ApplicationEvent
{
public:
  using Trigger_t = gsw::event_trigger<ApplicationEvent>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  virtual const char* Name() const {return "WindowEvent"; }

  EVENT_CATEGORY(EventCategory::Application)
  EVENT_TYPE(EventType::Window)
};

class WindowClose : public WindowEvent
{
public:
  using Trigger_t = gsw::event_trigger<WindowClose>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowClose(){}

  EVENT_TYPE(EventType::WindowClose)
};

class WindowResize : public WindowEvent
{
public:
  using Trigger_t = gsw::event_trigger<WindowResize>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

private:
  unsigned int mWidth;
  unsigned int mHeight;

public:
  WindowResize(unsigned int width, unsigned int height)
    : mWidth(width)
    , mHeight(height)
  {}

  virtual const char* Name() const {return "WindowResize"; }

  inline
  unsigned int
  Width() const
  {
    return mWidth;
  }

  inline
  unsigned int
  Height() const
  {
    return mHeight;
  }

  EVENT_TYPE(EventType::WindowResize)
};

class WindowGainedFocus : public WindowEvent
{
public:
  using Trigger_t = gsw::event_trigger<WindowGainedFocus>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowGainedFocus(){}

  virtual const char* Name() const {return "WindowGainedfocus"; }

  EVENT_TYPE(EventType::WindowFocus)
};

class WindowLostFocus : public WindowEvent
{
public:
  using Trigger_t = gsw::event_trigger<WindowLostFocus>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowLostFocus(){}

  virtual const char* Name() const {return "WindowLostfocus"; }

  EVENT_TYPE(EventType::WindowLostFocus)
};

class WindowMoved : public WindowEvent
{
public:
  using Trigger_t = gsw::event_trigger<WindowMoved>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowMoved(){}

  virtual const char* Name() const {return "WindowMoved"; }

  EVENT_TYPE(EventType::WindowMoved)
};

class AppTick : public ApplicationEvent
{
public:
  using Trigger_t = gsw::event_trigger<AppTick>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  AppTick(){}

  virtual const char* Name() const {return "AppTick"; }

  EVENT_TYPE(EventType::AppTick)
};

class AppUpdate : public ApplicationEvent
{
public:
  using Trigger_t = gsw::event_trigger<AppUpdate>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  AppUpdate(){}

  virtual const char* Name() const {return "AppUpdate"; }

  EVENT_TYPE(EventType::AppUpdate)
};

class AppRender : public ApplicationEvent
{
public:
  using Trigger_t = gsw::event_trigger<AppRender>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  AppRender(){}

  virtual const char* Name() const {return "AppRender"; }

  EVENT_TYPE(EventType::AppRender)
};

}

#endif //TEST_APPLICATIONEVENT_HH
