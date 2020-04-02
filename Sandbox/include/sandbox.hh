#ifndef TEST_SANDBOX_HH
#define TEST_SANDBOX_HH

#include "shader.hh"
#include "buffer.hh"

#include <Application.hh>
#include <vertex_array.hh>

class Sandbox : public Bandolier::Application
{
public:
  Sandbox();
  ~Sandbox() = default;
};

#endif //TEST_SANDBOX_HH
