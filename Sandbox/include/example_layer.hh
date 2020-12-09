#ifndef BANDOLIER_EXAMPLE_LAYER_HH
#define BANDOLIER_EXAMPLE_LAYER_HH

#include <layer.hh>
#include <shader.hh>
#include <vertex_array.hh>
#include <texture.hh>
#include <orthographic_camera_controller.hh>

class Example : public Bandolier::Layer {
private:
  Bandolier::ShaderLibrary mShaderLibrary;
  std::shared_ptr<Bandolier::VertexArray> mVAO;
  std::shared_ptr<Bandolier::VertexArray> mSquareVAO;
  std::shared_ptr<Bandolier::VertexArray> mTexVAO;
  std::shared_ptr<Bandolier::Texture2D> mTexture;
  std::shared_ptr<Bandolier::Texture2D> mAlphaTex;
  Bandolier::OrthographicCameraController mCameraController;
  glm::vec4 mSquareColor{ 0.2f, 0.3f, 0.8f, 1.0f };

  void RenderImGui();

  void RenderOpenGL();

public:
  Example();

  ~Example() override;

  void OnAttach() override;

  void OnDetach() override;

  void OnUpdate(Bandolier::time_step ts) override;

  bool OnEvent(const Bandolier::Events::BaseEvent& e) override;
};

#endif //BANDOLIER_EXAMPLE_LAYER_HH
