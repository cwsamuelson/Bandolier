#ifndef BANDOLIER_INPUT_HH
#define BANDOLIER_INPUT_HH

#include <tuple>

namespace Bandolier{

class Input{
public:
  inline static
  bool
  IsKeyPressed(int keycode){ return Instance->IsKeyPressedImpl(keycode); }
  inline static
  bool
  IsMouseButtonPressed(int button){ return Instance->IsMouseButtonPressedImpl(button); }
  inline static
  std::tuple<float, float>
  GetMousePosition(){ return Instance->GetMousePositionImpl(); }

protected:
  static Input* Instance;

  virtual bool
  IsKeyPressedImpl(int keycode) = 0;
  virtual bool
  IsMouseButtonPressedImpl(int button) = 0;
  virtual std::tuple<float, float>
  GetMousePositionImpl() = 0;
};

}

#endif //BANDOLIER_INPUT_HH
