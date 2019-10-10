#ifndef BANDOLIER_RENDERER_HH
#define BANDOLIER_RENDERER_HH

namespace Bandolier{

class Renderer
{
public:
  enum class API{
    None = 0,
    OpenGL,
    Direct3D,
    Vulkan,
    DirectX = int(Direct3D),
  };

  inline static API GetAPI(){ return sRendererAPI; }

private:
  inline static API sRendererAPI = API::OpenGL;
};

}

#endif //BANDOLIER_RENDERER_HH
