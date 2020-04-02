#ifndef TEST_EVENTS_HH
#define TEST_EVENTS_HH

#include <iostream>

#define BIT(N) (1 << N)
#define EVENT_CATEGORY(category) virtual unsigned short Categories() const override{ return category; }
#define EVENT_TYPE(type) virtual EventType Type() const override{ return type; }

namespace Bandolier::Events {

enum struct EventType {
  Unspecified = 0,
  Window,
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowGainedFocus,
  WindowMoved,
  App,
  AppTick,
  AppUpdate,
  AppRender,
  Key,
  KeyPressed,
  KeyReleased,
  KeyTyped,
  Mouse,
  MouseButton,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled,
};

enum EventCategory {
  None = 0, Application = BIT(1), Input = BIT(2), Keyboard = BIT(3), Mouse = BIT(4), MouseButton = BIT(5),
};

class BaseEvent {
public:
  virtual const char* Name() const = 0;

  virtual unsigned short Categories() const = 0;

  virtual EventType Type() const {
    return EventType::Unspecified;
  }

  inline bool HasCategory(EventCategory category) const {
    return Categories() & (unsigned short) (category);
  }
};

inline std::ostream& operator<<(std::ostream& os, const BaseEvent& e) {
  return os << e.Name();
}

class None : public BaseEvent {
  EVENT_CATEGORY(0)
};

}

#endif //TEST_EVENTS_HH
