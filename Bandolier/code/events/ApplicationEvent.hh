#ifndef TEST_APPLICATIONEVENT_HH
#define TEST_APPLICATIONEVENT_HH

#include <events.hh>

namespace Bandolier::Events {

class ApplicationEvent : public BaseEvent {
public:
  using Trigger_t = gsw::event_trigger<void(ApplicationEvent)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  [[nodiscard]]
  const char* Name() const override {
    return "ApplicationEvent";
  }

  EVENT_CATEGORY(EventCategory::Application)

  EVENT_TYPE(EventType::App)
};

class WindowEvent : public ApplicationEvent {
public:
  using Trigger_t = gsw::event_trigger<void(ApplicationEvent)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  [[nodiscard]]
  const char* Name() const override {
    return "WindowEvent";
  }

  EVENT_CATEGORY(EventCategory::Application)

  EVENT_TYPE(EventType::Window)
};

class WindowClose : public WindowEvent {
public:
  using Trigger_t = gsw::event_trigger<void(WindowClose)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowClose() = default;

  EVENT_TYPE(EventType::WindowClose)
};

class WindowResize : public WindowEvent {
public:
  using Trigger_t = gsw::event_trigger<void(WindowResize)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

private:
  unsigned int mWidth;
  unsigned int mHeight;

public:
  WindowResize(unsigned int width, unsigned int height)
          : mWidth(width)
          , mHeight(height) {
  }

  [[nodiscard]]
  const char* Name() const override {
    return "WindowResize";
  }

  [[nodiscard]]
  inline unsigned int Width() const {
    return mWidth;
  }

  [[nodiscard]]
  inline unsigned int Height() const {
    return mHeight;
  }

  EVENT_TYPE(EventType::WindowResize)
};

class WindowGainedFocus : public WindowEvent {
public:
  using Trigger_t = gsw::event_trigger<void(WindowGainedFocus)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowGainedFocus() = default;

  [[nodiscard]]
  const char* Name() const override {
    return "WindowGainedfocus";
  }

  EVENT_TYPE(EventType::WindowGainedFocus)
};

class WindowLostFocus : public WindowEvent {
public:
  using Trigger_t = gsw::event_trigger<void(WindowLostFocus)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowLostFocus() = default;

  [[nodiscard]]
  const char* Name() const override {
    return "WindowLostfocus";
  }

  EVENT_TYPE(EventType::WindowLostFocus)
};

class WindowMoved : public WindowEvent {
public:
  using Trigger_t = gsw::event_trigger<void(WindowMoved)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  WindowMoved() = default;

  [[nodiscard]]
  const char* Name() const override {
    return "WindowMoved";
  }

  EVENT_TYPE(EventType::WindowMoved)
};

class AppTick : public ApplicationEvent {
public:
  using Trigger_t = gsw::event_trigger<void(AppTick)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  AppTick() = default;

  [[nodiscard]]
  const char* Name() const override {
    return "AppTick";
  }

  EVENT_TYPE(EventType::AppTick)
};

class AppUpdate : public ApplicationEvent {
public:
  using Trigger_t = gsw::event_trigger<void(AppUpdate)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  AppUpdate() = default;

  [[nodiscard]]
  const char* Name() const override {
    return "AppUpdate";
  }

  EVENT_TYPE(EventType::AppUpdate)
};

class AppRender : public ApplicationEvent {
public:
  using Trigger_t = gsw::event_trigger<void(AppRender)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  AppRender() = default;

  [[nodiscard]]
  const char* Name() const override {
    return "AppRender";
  }

  EVENT_TYPE(EventType::AppRender)
};

}

#endif //TEST_APPLICATIONEVENT_HH
