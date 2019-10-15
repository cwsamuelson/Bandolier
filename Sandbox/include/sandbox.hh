#ifndef TEST_SANDBOX_HH
#define TEST_SANDBOX_HH

#include "Renderer/shader.hh"
#include "Renderer/buffer.hh"

#include <Application.hh>
#include <Renderer/vertex_array.hh>

class Example : public Bandolier::Layer
{
private:
  std::shared_ptr<Bandolier::Shader> mColorShader;
  std::shared_ptr<Bandolier::Shader> mShader;
  std::shared_ptr<Bandolier::VertexArray> mVAO;
  std::shared_ptr<Bandolier::VertexArray> mSquareVAO;
  Bandolier::OrthographicCamera mCamera;

public:
  Example();
  ~Example();

  void
  OnAttach();
  void
  OnDetach();
  void
  OnUpdate();
  bool
  OnEvent(const Bandolier::Events::BaseEvent& e);
};

class Sandbox : public Bandolier::Application
{
public:
  Sandbox();
  ~Sandbox() = default;
};

#endif //TEST_SANDBOX_HH
