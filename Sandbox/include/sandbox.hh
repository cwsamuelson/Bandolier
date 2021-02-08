#ifndef TEST_SANDBOX_HH
#define TEST_SANDBOX_HH

#include "shader.hh"
#include "buffer.hh"

#include <Application.hh>
#include <vertex_array.hh>

namespace Sandbox {

class Application : public Bandolier::Application {
public:
  Application();

  ~Application() override = default;
};

}

#endif //TEST_SANDBOX_HH
