#ifndef TEST_APPLICATION_HH
#define TEST_APPLICATION_HH

#include <memory>

namespace Bandolier {

class application
{
public:
  application() = default;
  virtual ~application() = default;

  virtual void run() = 0;
};

using AppPtr = std::unique_ptr<application>;
// To be defined by the client
AppPtr CreateApplication();

}

#endif //TEST_APPLICATION_HH
