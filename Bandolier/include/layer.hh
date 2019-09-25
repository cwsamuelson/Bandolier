#ifndef TEST_LAYER_HH
#define TEST_LAYER_HH

#include <string>

namespace Bandolier {

class Layer
{
public:
  Layer(std::string name = "Layer")
    : mDebugName(std::move(name))
  {}
  virtual ~Layer() = default;

  virtual void
  OnAttach() {}
  virtual void
  OnDetach() {}
  virtual void
  OnUpdate() {}

  inline
  const std::string&
  Name() const
  {
    return mDebugName;
  }

protected:
  std::string mDebugName;
};

}

#endif //TEST_LAYER_HH
