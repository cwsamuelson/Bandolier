#include "layer_stack.hh"

namespace Bandolier {

LayerStack::LayerStack()
  : mSplitIndex(0)
{}

void
LayerStack::PushLayer(value_type layer)
{
  mLayers.emplace(mLayers.begin() + mSplitIndex, layer);
  ++mSplitIndex;
}

void
LayerStack::PopLayer()
{
  mLayers.erase(mLayers.begin() + mSplitIndex);
  --mSplitIndex;
}

void
LayerStack::EraseLayer(value_type layer)
{
  auto it = std::find(mLayers.begin(), mLayers.begin() + mSplitIndex, layer);
  if(it != mLayers.begin() + mSplitIndex)
  {
    mLayers.erase(it);
  }
}

void
LayerStack::PushOverlay(value_type overlay)
{
  mLayers.emplace_back(overlay);
}

void
LayerStack::PopOverlay()
{
  mLayers.pop_back();
}

void
LayerStack::EraseOverlay(value_type overlay)
{
  auto it = std::find(mLayers.begin() + mSplitIndex, mLayers.end(), overlay);
  if(it != mLayers.end())
  {
    mLayers.erase(it);
  }
}

}
