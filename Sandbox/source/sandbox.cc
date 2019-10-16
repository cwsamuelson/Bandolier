#include <iostream>

#include <entrypoint.hh>
#include <imgui/imgui_layer.hh>
#include "../../Bandolier/vendor/glm/glm/gtc/matrix_transform.hpp"

#include "example_layer.hh"

#include "sandbox.hh"

Sandbox::Sandbox()
  : Application("Sandbox")
{
  //! @TODO use member-initialization?
  PushLayer(std::make_shared<Example>());
}

Bandolier::Application& Bandolier::CreateApplication()
{
  Application::Instance = new Sandbox;
  return Application::Get();
}

