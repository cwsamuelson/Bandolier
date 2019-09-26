#ifndef TEST_APPLICATION_HH
#define TEST_APPLICATION_HH

#include <memory>

#include <event_handler.hh>

#include <layer_stack.hh>
#include <ApplicationEvent.hh>
#include <Windo.hh>

namespace Bandolier {

class Application
{
protected:
  std::unique_ptr<Window> mWindow;
  bool mRunning = false;
  LayerStack mLayerStack;

public:
  Application();
  virtual ~Application();

  virtual void
  run() = 0;

  virtual void
  PushLayer(LayerStack::value_type layer);
  virtual void
  PushOverlay(LayerStack::value_type overlay);
};

using AppPtr = std::unique_ptr<Application>;
// To be defined by the client
AppPtr CreateApplication();

}

#endif //TEST_APPLICATION_HH
