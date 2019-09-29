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
  OnUpdate() override;
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
  MouseButtonPressed(const Bandolier::Events::BaseEvent& e)
  {
    auto& event = static_cast<const Events::MouseButtonPressed&>(e);
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.MouseButton()] = true;
    return false;
  }

  bool
  MouseButtonReleased(const Bandolier::Events::BaseEvent& e)
  {
    auto& event = static_cast<const Events::MouseButtonReleased&>(e);
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.MouseButton()] = false;
    return false;
  }

  bool
  MouseMoved(const Bandolier::Events::BaseEvent& e)
  {
    auto& event = static_cast<const Events::MouseMoved&>(e);
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(event.X(), event.Y());
    return false;
  }

  bool
  MouseScrolled(const Bandolier::Events::BaseEvent& e)
  {
    auto& event = static_cast<const Events::MouseScrolled&>(e);
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += event.XOffset();
    io.MouseWheel += event.YOffset();
    return false;
  }

  bool
  KeyPressed(const Bandolier::Events::BaseEvent& e)
  {
    auto& event = static_cast<const Events::KeyPressed&>(e);
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[event.KeyCode()] = true;

    io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]   || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT]     || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]   || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    return false;
  }

  bool
  KeyReleased(const Bandolier::Events::BaseEvent& e)
  {
    auto& event = static_cast<const Events::KeyReleased&>(e);
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[event.KeyCode()] = false;

    io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]   || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT]     || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]   || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    return false;
  }

  bool
  KeyTyped(const Bandolier::Events::BaseEvent& e)
  {
    auto& event = static_cast<const Events::KeyEvent&>(e);
    ImGuiIO& io = ImGui::GetIO();
    int keycode = event.KeyCode();
    if(keycode > 0 && keycode < 0x10000)
    {
      io.AddInputCharacter((unsigned short)keycode);
    }

    return false;
  }

  bool
  WindowResize(const Bandolier::Events::BaseEvent& e)
  {
    auto& event = static_cast<const Events::WindowResize&>(e);
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(event.Width(), event.Height());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    glViewport(0, 0, event.Width(), event.Height());
    return false;
  }
};

}

#endif //BANDOLIER_IMGUI_LAYER_HH
