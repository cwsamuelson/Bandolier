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
};

class WindowClose : public ApplicationEvent
{
public:
  using Trigger_t = gsw::event_trigger<WindowClose>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowClose(){}
};

class WindowResize : public ApplicationEvent
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
};

class WindowGainedFocus : public ApplicationEvent
{
public:
  using Trigger_t = gsw::event_trigger<WindowGainedFocus>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowGainedFocus(){}

  virtual const char* Name() const {return "WindowGainedfocus"; }
};

class WindowLostFocus : public ApplicationEvent
{
public:
  using Trigger_t = gsw::event_trigger<WindowLostFocus>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowLostFocus(){}

  virtual const char* Name() const {return "WindowLostfocus"; }
};

class WindowMoved : public ApplicationEvent
{
public:
  using Trigger_t = gsw::event_trigger<WindowMoved>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowMoved(){}

  virtual const char* Name() const {return "WindowMoved"; }
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
};

}

#endif //TEST_APPLICATIONEVENT_HH
