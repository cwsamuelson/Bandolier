#ifndef BANDOLIER_EXAMPLE_LAYER_HH
#define BANDOLIER_EXAMPLE_LAYER_HH

#include <layer.hh>
#include <Renderer/shader.hh>
#include <Renderer/vertex_array.hh>
#include <Renderer/orthographic_camera.hh>
#include <Renderer/texture.hh>

class Example : public Bandolier::Layer
{
private:
  std::shared_ptr<Bandolier::Shader> mColorShader;
  std::shared_ptr<Bandolier::Shader> mShader;
  std::shared_ptr<Bandolier::Shader> mTextureShader;
  std::shared_ptr<Bandolier::VertexArray> mVAO;
  std::shared_ptr<Bandolier::VertexArray> mSquareVAO;
  std::shared_ptr<Bandolier::Texture2D> mTexture;
  Bandolier::OrthographicCamera mCamera;
  glm::vec3 mSquareColor{0.2f, 0.3f, 0.8f};

public:
  Example();
  ~Example();

  void
  OnAttach();
  void
  OnDetach();
  void
  OnUpdate(Bandolier::time_step ts);
  bool
  OnEvent(const Bandolier::Events::BaseEvent& e);
};

#endif //BANDOLIER_EXAMPLE_LAYER_HH
