#ifndef TEST_APPLICATION_HH
#define TEST_APPLICATION_HH

#include <memory>

#include <event_handler.hh>

#include <ApplicationEvent.hh>

namespace Bandolier {

class application
{
public:
  using AppTrigger = gsw::event_trigger<Events::ApplicationEvent&>;
  using AppChannel = AppTrigger::channel_t;

protected:
  AppTrigger mAppTrigger;

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
