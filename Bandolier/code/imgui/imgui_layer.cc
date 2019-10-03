#include "imgui_layer.hh"

#include <imgui.h>

#include <GLFW/glfw3.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "Application.hh"
#include "logger.hh"

namespace Bandolier{

ImguiLayer::ImguiLayer()
  : Layer("ImGuiLayer")
{}

void
ImguiLayer::OnAttach()
{
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGuiIO& io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
  io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
  io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
  io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
  io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
  io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
  io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
  io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
  io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
  io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
  io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
  io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
  io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
  io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
  io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
  io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

  ImGui_ImplOpenGL3_Init("#version 410");

  mTime = float(glfwGetTime());
}

void
ImguiLayer::OnDetach()
{}

void
ImguiLayer::OnUpdate()
{
  ImGuiIO& io = ImGui::GetIO();
  Application& app = Application::Get();
  Window& window = app.Window();
  io.DisplaySize = ImVec2(window.Width(), window.Height());

  float time = float(glfwGetTime());
  io.DeltaTime = time - mTime;
  mTime = time;

  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  static bool show = true;
  ImGui::ShowDemoWindow(&show);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool
ImguiLayer::OnEvent(const Bandolier::Events::BaseEvent& e)
{
  if(mEventHandlers.count(e.Type()))
  {
    return std::invoke(mEventHandlers.at(e.Type()), this, e);
  }

  return false;
}

bool
ImguiLayer::MouseButtonPressed(const Bandolier::Events::BaseEvent& e)
{
  auto& event = static_cast<const Events::MouseButtonPressed&>(e);
  ImGuiIO& io = ImGui::GetIO();
  io.MouseDown[event.MouseButton()] = true;
  return false;
}

bool
ImguiLayer::MouseButtonReleased(const Bandolier::Events::BaseEvent& e)
{
  auto& event = static_cast<const Events::MouseButtonReleased&>(e);
  ImGuiIO& io = ImGui::GetIO();
  io.MouseDown[event.MouseButton()] = false;
  return false;
}

bool
ImguiLayer::MouseMoved(const Bandolier::Events::BaseEvent& e)
{
  auto& event = static_cast<const Events::MouseMoved&>(e);
  ImGuiIO& io = ImGui::GetIO();
  io.MousePos = ImVec2(event.X(), event.Y());
  return false;
}

bool
ImguiLayer::MouseScrolled(const Bandolier::Events::BaseEvent& e)
{
  auto& event = static_cast<const Events::MouseScrolled&>(e);
  ImGuiIO& io = ImGui::GetIO();
  io.MouseWheelH += event.XOffset();
  io.MouseWheel += event.YOffset();
  return false;
}

bool
ImguiLayer::KeyPressed(const Bandolier::Events::BaseEvent& e)
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
ImguiLayer::KeyReleased(const Bandolier::Events::BaseEvent& e)
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
ImguiLayer::KeyTyped(const Bandolier::Events::BaseEvent& e)
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
ImguiLayer::WindowResize(const Bandolier::Events::BaseEvent& e)
{
  auto& event = static_cast<const Events::WindowResize&>(e);
  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize = ImVec2(event.Width(), event.Height());
  io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
  glViewport(0, 0, event.Width(), event.Height());
  return false;
}

}
