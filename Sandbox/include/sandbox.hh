#ifndef TEST_SANDBOX_HH
#define TEST_SANDBOX_HH

#include <application.hh>

class sandbox : public Bandolier::application
{
public:
  sandbox() = default;
  ~sandbox() = default;

  void run() override;
};

#endif //TEST_SANDBOX_HH
