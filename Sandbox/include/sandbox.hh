#ifndef TEST_SANDBOX_HH
#define TEST_SANDBOX_HH

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
};

#endif //TEST_SANDBOX_HH
