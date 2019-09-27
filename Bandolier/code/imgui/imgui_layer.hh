#ifndef BANDOLIER_IMGUI_LAYER_HH
#define BANDOLIER_IMGUI_LAYER_HH

#include "layer.hh"
#include "events.hh"

namespace Bandolier {

class ImguiLayer : public Layer
{
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

private:
  float
  mTime = 0.0f;
};

}

#endif //BANDOLIER_IMGUI_LAYER_HH
