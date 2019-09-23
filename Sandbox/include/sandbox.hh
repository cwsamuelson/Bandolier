#ifndef TEST_SANDBOX_HH
#define TEST_SANDBOX_HH

#include <Application.hh>

class Sandbox : public Bandolier::Application
{
public:
  Sandbox() = default;
  ~Sandbox() = default;

  void run() override;
};

#endif //TEST_SANDBOX_HH
