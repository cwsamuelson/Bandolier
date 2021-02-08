#ifndef BANDOLIER_GUI_LAYER_HH
#define BANDOLIER_GUI_LAYER_HH

#include <imgui_layer.hh>

#include <glm/ext.hpp>

namespace Sandbox {

class GuiLayer : public Bandolier::ImguiLayer {
public:
  void OnUpdate(Bandolier::time_step ts) override;

private:
  glm::vec4 mSquareColor;
};

}

#endif //BANDOLIER_GUI_LAYER_HH
