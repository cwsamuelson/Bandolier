#ifndef TEST_SANDBOX_HH
#define TEST_SANDBOX_HH

#include"Renderer/shader.hh"

#include <Application.hh>

class Sandbox : public Bandolier::Application
{
public:
  Sandbox();
  ~Sandbox() = default;

  void run() override;

private:
  unsigned int mVAO;
  unsigned int mVBO;
  unsigned int mIBO;
  std::unique_ptr<Bandolier::Shader> mShader;
};

#endif //TEST_SANDBOX_HH
