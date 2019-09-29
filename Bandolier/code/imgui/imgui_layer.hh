#ifndef BANDOLIER_IMGUI_LAYER_HH
#define BANDOLIER_IMGUI_LAYER_HH

#include <unordered_map>

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
  OnUpdate() override;
  bool
  OnEvent(const Events::BaseEvent& e) override;

protected:
  using event_callback = bool(ImguiLayer::*)(const Bandolier::Events::BaseEvent&);
  std::unordered_map<Bandolier::Events::EventType, event_callback> mEventHandlers =
  {
    {Events::EventType::Unspecified,         &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::Window,              &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::WindowClose,         &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::WindowResize,        &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::WindowFocus,         &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::WindowLostFocus,     &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::WindowGainedFocus,   &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::WindowMoved,         &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::App,                 &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::AppTick,             &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::AppUpdate,           &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::AppRender,           &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::Key,                 &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::KeyPressed,          &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::KeyReleased,         &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::KeyTyped,            &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::Mouse,               &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::MouseButton,         &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::MouseButtonPressed,  &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::MouseButtonReleased, &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::MouseMoved,          &ImguiLayer::UnspecifiedEvent},
    {Events::EventType::MouseScrolled,       &ImguiLayer::UnspecifiedEvent},
  };

  bool
  UnspecifiedEvent(const Bandolier::Events::BaseEvent& e)
  {
    logging::client()->warn("Unhandled event type {0} occurred.", e.Type());
    return false;
  }
};

}

#endif //BANDOLIER_IMGUI_LAYER_HH
