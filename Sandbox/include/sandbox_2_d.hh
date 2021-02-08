#ifndef BANDOLIER_SANDBOX_2_D_HH
#define BANDOLIER_SANDBOX_2_D_HH

#include <layer.hh>
#include <vertex_array.hh>
#include <orthographic_camera_controller.hh>
#include <shader.hh>

#include <memory>

class Sandbox2d : public Bandolier::Layer {
private:
  Bandolier::OrthographicCameraController mCameraController;

  std::shared_ptr<Bandolier::VertexArray> mSquare;
  std::shared_ptr<Bandolier::Shader> mShader;

  glm::vec4 mSquareColor;

  void OpenGLRender();

public:
  Sandbox2d();

  void OnUpdate(Bandolier::time_step ts) override;
};

#endif //BANDOLIER_SANDBOX_2_D_HH
