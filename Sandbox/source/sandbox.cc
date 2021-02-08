#include <iostream>

#include <entrypoint.hh>
#include <imgui_layer.hh>
#include <gui_layer.hh>
#include "glm/gtc/matrix_transform.hpp"

#include "example_layer.hh"
#include "sandbox_2_d.hh"

#include "sandbox.hh"

namespace Sandbox {

Application::Application()
        : Bandolier::Application("Sandbox") {
}

}

Bandolier::Application& Bandolier::CreateApplication() {
  Application::Instance = new Sandbox::Application;
  Application::Instance->PushLayer(std::make_shared<Example>());
  Application::Instance->PushLayer(std::make_shared<Sandbox2d>());
  Application::Instance->PushLayer(std::make_shared<Sandbox::GuiLayer>());
  return Application::Get();
}

