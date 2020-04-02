#include "imgui_layer.hh"

#include <imgui.h>

#include <key_codes.hh>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "Application.hh"
#include "logger.hh"

namespace Bandolier {

ImguiLayer::ImguiLayer()
        : Layer("ImGuiLayer") {
}

void ImguiLayer::OnAttach() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui::StyleColorsDark();

  ImGuiStyle& style = ImGui::GetStyle();
  if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.5f;
    style.Colors[ImGuiCol_WindowBg].w = 0.5f;
  }

  ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::Get().Window().Native()), true);
  ImGui_ImplOpenGL3_Init("#version 450");
}

void ImguiLayer::OnDetach() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImguiLayer::OnUpdate(time_step) {
  //static bool show = true;
  //ImGui::ShowDemoWindow(&show);
}

void ImguiLayer::Begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImguiLayer::End() {
  ImGuiIO& io = ImGui::GetIO();
  Application& app = Application::Get();
  Window& window = app.Window();
  io.DisplaySize = ImVec2(float(window.Width()), float(window.Height()));

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* backup = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup);
  }
}

bool ImguiLayer::OnEvent(const Bandolier::Events::BaseEvent& e) {
  if(mEventHandlers.count(e.Type())) {
    return std::invoke(mEventHandlers.at(e.Type()), this, e);
  }

  return false;
}

/*bool
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
  io.DisplaySize = ImVec2(float(event.Width()), float(event.Height()));
  io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
  glViewport(0, 0, event.Width(), event.Height());
  return false;
}*/

}
