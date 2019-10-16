#ifndef TEST_LAYER_HH
#define TEST_LAYER_HH

#include <string>

#include "events.hh"

namespace Bandolier {

using time_step = float;
using time_point = float;

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
  OnUpdate(time_step ts) {}
  virtual bool
  OnEvent(const Events::BaseEvent& e) { return false; }

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
