#ifndef TEST_SANDBOX_HH
#define TEST_SANDBOX_HH

#include "Renderer/shader.hh"
#include "Renderer/buffer.hh"

#include <Application.hh>
#include <Renderer/vertex_array.hh>

class Sandbox : public Bandolier::Application
{
public:
  Sandbox();
  ~Sandbox() = default;
};

#endif //TEST_SANDBOX_HH
