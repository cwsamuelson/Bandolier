#ifndef TEST_MOUSEEVENTS_HH
#define TEST_MOUSEEVENTS_HH

#include <event_handler.hh>

#include <events.hh>

namespace Bandolier::Events {

class MouseEvent : public BaseEvent {
public:
  using Trigger_t = gsw::event_trigger<void(MouseEvent)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  [[nodiscard]]
  const char* Name() const override{
    return "MouseEvent";
  }

  EVENT_CATEGORY(EventCategory::Mouse | EventCategory::Input)

  EVENT_TYPE(EventType::Mouse)
};

class MouseButtonEvent : public MouseEvent {
public:
  using Trigger_t = gsw::event_trigger<void(MouseButtonEvent)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

public:
  [[nodiscard]]
  inline int MouseButton() const {
    return mButton;
  }

  EVENT_TYPE(EventType::MouseButton)

protected:
  explicit
  MouseButtonEvent(int button)
          : mButton(button) {
  }

  [[nodiscard]]
  const char* Name() const override{
    return "MouseButtonEvent";
  }

  EVENT_CATEGORY(EventCategory::Mouse | EventCategory::MouseButton | EventCategory::Input)

  int mButton;
};

class MouseButtonPressed : public MouseButtonEvent {
public:
  using Trigger_t = gsw::event_trigger<void(MouseButtonPressed)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  explicit
  MouseButtonPressed(int button)
          : MouseButtonEvent(button) {
  }

  [[nodiscard]]
  const char* Name() const override{
    return "MouseButtonPressed";
  }

  EVENT_TYPE(EventType::MouseButtonPressed)
};

class MouseButtonReleased : public MouseButtonEvent {
public:
  using Trigger_t = gsw::event_trigger<void(MouseButtonReleased)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  explicit
  MouseButtonReleased(int button)
          : MouseButtonEvent(button) {
  }

  [[nodiscard]]
  const char* Name() const override {
    return "MouseButtonReleased";
  }

  EVENT_TYPE(EventType::MouseButtonReleased)
};

class MouseMoved : public MouseEvent {
public:
  using Trigger_t = gsw::event_trigger<void(MouseMoved)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  MouseMoved(float x, float y)
          : mX(x)
          , mY(y) {
  }

  [[nodiscard]]
  const char* Name() const override {
    return "MouseMoved";
  }

  [[nodiscard]]
  inline float X() const {
    return mX;
  }

  [[nodiscard]]
  inline float Y() const {
    return mY;
  }

  [[nodiscard]]
  inline std::pair<float, float> position() const {
    return { mX, mY };
  }

  EVENT_TYPE(EventType::MouseMoved)

private:
  float mX;
  float mY;
};

class MouseScrolled : public MouseEvent {
public:
  using Trigger_t = gsw::event_trigger<void(MouseScrolled)>;
  using Channel_t = Trigger_t::channel_t;
  using Handler_t = Channel_t::handler;
  using SimpleHandler_t = Channel_t::simple_handler;

  MouseScrolled(float xOffset, float yOffset)
          : mXOffset(xOffset)
          , mYOffset(yOffset) {
  }

  [[nodiscard]]
  const char* Name() const override {
    return "MouseScrolled";
  }

  [[nodiscard]]
  inline float XOffset() const {
    return mXOffset;
  }

  [[nodiscard]]
  inline float YOffset() const {
    return mYOffset;
  }

  [[nodiscard]]
  inline std::pair<float, float> Offset() const {
    return { mXOffset, mYOffset };
  }

  EVENT_TYPE(EventType::MouseScrolled)

private:
  float mXOffset;
  float mYOffset;
};

}

#endif //TEST_MOUSEEVENTS_HH
