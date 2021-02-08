#include "gui_layer.hh"

using namespace Bandolier;

namespace Sandbox{

void GuiLayer::OnUpdate(time_step ts) {
  ImguiLayer::Begin();
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
  ImGui::End();
  ImguiLayer::End();
}

}
