#include <GLFW/glfw3.h>

#include "Application.hh"

#include "windows_input.hh"

namespace Bandolier {

std::unique_ptr<Input> Input::Instance = std::make_unique<WindowsInput>();

bool WindowsInput::IsKeyPressedImpl(int keycode) {
  auto window = static_cast<GLFWwindow*>(Application::Get().Window().Native());
  auto state = glfwGetKey(window, keycode);
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(int button) {
  auto window = static_cast<GLFWwindow*>(Application::Get().Window().Native());
  auto state = glfwGetMouseButton(window, button);
  return state == GLFW_PRESS;
}

std::tuple<float, float> WindowsInput::GetMousePositionImpl() {
  auto window = static_cast<GLFWwindow*>(Application::Get().Window().Native());
  double X;
  double Y;
  glfwGetCursorPos(window, &X, &Y);
  return { float(X), float(Y) };
}

}