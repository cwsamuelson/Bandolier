#ifndef TEST_APPLICATION_HH
#define TEST_APPLICATION_HH

#include <memory>

#include <event_handler.hh>

#include "imgui_layer.hh"
#include <layer_stack.hh>
#include <ApplicationEvent.hh>
#include <Window.hh>
#include <orthographic_camera.hh>

namespace Bandolier {

class Application;

// To be defined by the client
Application& CreateApplication();

class Application {
protected:
  friend Application& Bandolier::CreateApplication();

  inline static Application* Instance = nullptr;

  std::unique_ptr<Bandolier::Window> mWindow;
  bool mRunning = false;
  bool mMinimized = false;
  LayerStack mLayerStack;
  time_point mLastTime = 0.0f;
  std::shared_ptr<ImguiLayer> mImguiLayer;

public:
  explicit Application(std::string WindowName = "Bandolier",
                       std::tuple<unsigned int, unsigned int> dims = { 1280, 720 });

  virtual ~Application() = default;

  virtual void run() final;

  [[nodiscard]]
  Bandolier::Window& Window() {
    return *mWindow;
  }

  [[nodiscard]]
  const Bandolier::Window& Window() const {
    return *mWindow;
  }

  //Using a static app instance allows the application to be accessed using only this base class,
  // and without knowledge of the client's implimentation.
  static Application& Get() {
    return *Instance;
  }

  virtual void PushLayer(LayerStack::value_type layer);

  virtual void PushOverlay(LayerStack::value_type overlay);
};

}

#endif //TEST_APPLICATION_HH
