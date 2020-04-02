#ifndef BANDOLIER_GRAPHICSCONTEXT_HH
#define BANDOLIER_GRAPHICSCONTEXT_HH

namespace Bandolier {

class GraphicsContext
{
public:
  virtual ~GraphicsContext() = default;

  virtual void
  SwapBuffers() = 0;
};

}

#endif //BANDOLIER_GRAPHICSCONTEXT_HH
