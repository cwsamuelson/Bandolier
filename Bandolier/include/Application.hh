#ifndef TEST_APPLICATION_HH
#define TEST_APPLICATION_HH

#include <memory>

#include <event_handler.hh>

#include <ApplicationEvent.hh>
#include <Windo.hh>

namespace Bandolier {

class Application
{
public:
  using AppTrigger = gsw::event_trigger<Events::ApplicationEvent&>;
  using AppChannel = AppTrigger::channel_t;

protected:
  AppTrigger mAppTrigger;
  std::unique_ptr<Window> mWindow;

private:
  bool mRunning = false;

public:
  Application();
  virtual ~Application();

  virtual void
  run() = 0;
};

using AppPtr = std::unique_ptr<Application>;
// To be defined by the client
AppPtr CreateApplication();

}

#endif //TEST_APPLICATION_HH
