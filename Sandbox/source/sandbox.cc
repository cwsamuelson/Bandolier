#include <iostream>

#include <entrypoint.hh>
#include <imgui_layer.hh>
#include "glm/gtc/matrix_transform.hpp"

#include "example_layer.hh"
#include "sandbox_2_d.hh"

#include "sandbox.hh"

Sandbox::Sandbox()
        : Application("Sandbox") {
  //! @TODO use member-initialization?
  PushLayer(std::make_shared<Example>());
  PushLayer(std::make_shared<Sandbox2d>());
}

Bandolier::Application& Bandolier::CreateApplication() {
  Application::Instance = new Sandbox;
  return Application::Get();
}

