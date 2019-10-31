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
  Bandolier::ShaderLibrary mShaderLibrary;
  std::shared_ptr<Bandolier::VertexArray> mVAO;
  std::shared_ptr<Bandolier::VertexArray> mSquareVAO;
  std::shared_ptr<Bandolier::VertexArray> mTexVAO;
  std::shared_ptr<Bandolier::Texture2D> mTexture;
  std::shared_ptr<Bandolier::Texture2D> mAlphaTex;
  Bandolier::OrthographicCamera mCamera;
  glm::vec3 mSquareColor{0.2f, 0.3f, 0.8f};

  void
  RenderImGui();
  void
  RenderOpenGL();

public:
  Example();
  ~Example();

  void
  OnAttach() override;
  void
  OnDetach() override;
  void
  OnUpdate(Bandolier::time_step ts) override;
  bool
  OnEvent(const Bandolier::Events::BaseEvent& e) override;
};

#endif //BANDOLIER_EXAMPLE_LAYER_HH
