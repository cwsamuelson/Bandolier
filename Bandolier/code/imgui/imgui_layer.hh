#ifndef BANDOLIER_IMGUI_LAYER_HH
#define BANDOLIER_IMGUI_LAYER_HH

#include <unordered_map>

#include <imgui.h>

#include <MouseEvents.hh>
#include <KeyEvent.hh>
#include <GLFW/glfw3.h>
#include <ApplicationEvent.hh>

#include "layer.hh"
#include "events.hh"
#include "logger.hh"

namespace Bandolier {

class ImguiLayer : public Layer
{
protected:
  float
  mTime = 0.0f;

public:
  ImguiLayer();
  ~ImguiLayer() = default;

  void
  OnAttach() override;
  void
  OnDetach() override;
  void
  OnUpdate(time_step ts) override;
  bool
  OnEvent(const Events::BaseEvent& e) override;

protected:
  using event_callback = bool(ImguiLayer::*)(const Bandolier::Events::BaseEvent&);
  std::unordered_map<Bandolier::Events::EventType, event_callback> mEventHandlers =
  {
    //{Events::EventType::Unspecified,         &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::Window,              &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::WindowClose,         &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::WindowResize,        &ImguiLayer::WindowResize},
    //{Events::EventType::WindowFocus,         &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::WindowLostFocus,     &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::WindowGainedFocus,   &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::WindowMoved,         &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::App,                 &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::AppTick,             &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::AppUpdate,           &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::AppRender,           &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::Key,                 &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::KeyPressed,          &ImguiLayer::KeyPressed},
    {Events::EventType::KeyReleased,         &ImguiLayer::KeyReleased},
    {Events::EventType::KeyTyped,            &ImguiLayer::KeyTyped},
    //{Events::EventType::Mouse,               &ImguiLayer::UnspecifiedEvent},
    //{Events::EventType::MouseButton,         &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::MouseButtonPressed,  &ImguiLayer::MouseButtonPressed},
    {Events::EventType::MouseButtonReleased, &ImguiLayer::MouseButtonReleased},
    {Events::EventType::MouseMoved,          &ImguiLayer::MouseMoved},
    {Events::EventType::MouseScrolled,       &ImguiLayer::MouseScrolled},
  };

  bool
  UnspecifiedEvent(const Bandolier::Events::BaseEvent& e)
  {
    logging::client()->warn("Unhandled event type {0} occurred.", e.Type());
    return false;
  }

  bool
  MouseButtonPressed(const Bandolier::Events::BaseEvent& e);

  bool
  MouseButtonReleased(const Bandolier::Events::BaseEvent& e);

  bool
  MouseMoved(const Bandolier::Events::BaseEvent& e);

  bool
  MouseScrolled(const Bandolier::Events::BaseEvent& e);

  bool
  KeyPressed(const Bandolier::Events::BaseEvent& e);

  bool
  KeyReleased(const Bandolier::Events::BaseEvent& e);

  bool
  KeyTyped(const Bandolier::Events::BaseEvent& e);

  bool
  WindowResize(const Bandolier::Events::BaseEvent& e);
};

}

#endif //BANDOLIER_IMGUI_LAYER_HH
