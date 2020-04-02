#ifndef BANDOLIER_WINDOWS_INPUT_HH
#define BANDOLIER_WINDOWS_INPUT_HH

#include <Input.hh>

namespace Bandolier {

class WindowsInput : public Input {
protected:
  virtual bool IsKeyPressedImpl(int keycode) override;

  virtual bool IsMouseButtonPressedImpl(int button) override;

  virtual std::tuple<float, float> GetMousePositionImpl() override;
};

}

#endif //BANDOLIER_WINDOWS_INPUT_HH
