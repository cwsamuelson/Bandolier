#ifndef TEST_LAYER_STACK_HH
#define TEST_LAYER_STACK_HH

#include <vector>
#include <memory>

#include "layer.hh"

namespace Bandolier {

class LayerStack
{
public:
  using container = std::vector<std::shared_ptr<Bandolier::Layer>>;
  using iterator = container::iterator;
  using reverse_iterator = container::reverse_iterator;
  using const_iterator = container::const_iterator;
  using value_type = container::value_type;
  using size_type = container::size_type;

private:
  container mLayers;
  size_type mSplitIndex;

public:
  LayerStack();
  ~LayerStack() = default;

  void
  PushLayer(value_type layer);
  void
  PopLayer();
  void
  EraseLayer(value_type layer);
  void
  PushOverlay(value_type overlay);
  void
  PopOverlay();
  void
  EraseOverlay(value_type overlay);

  iterator
  begin()
  {
    return mLayers.begin();
  }

  iterator
  end()
  {
    return mLayers.end();
  }

  const_iterator
  cbegin() const
  {
    return mLayers.cbegin();
  }

  const_iterator
  cend()
  {
    return mLayers.cend();
  }

  reverse_iterator
  rbegin()
  {
    return mLayers.rbegin();
  }

  reverse_iterator
  rend()
  {
    return mLayers.rend();
  }
};

}

#endif //TEST_LAYER_STACK_HH
