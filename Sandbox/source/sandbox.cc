#include <iostream>

#include "entrypoint.hh"
#include <logger.hh>
#include <ApplicationEvent.hh>

#include "sandbox.hh"

using WindowResizeEvent = Bandolier::Events::WindowResize;

void Sandbox::run()
{
  using Event = WindowResizeEvent;
  using ChannelPtr = std::weak_ptr<Event::Channel_t>;
  Event::Trigger_t WindowResizeTrigger;
  ChannelPtr WindowResizeChannelPtr = WindowResizeTrigger.getChannel();
  WindowResizeChannelPtr.lock()->subscribe(
    [](const WindowResizeEvent& e)
    {
      Bandolier::logging::client()->warn("Window resize event happened!\tNew dimensions are {0}, {1}", e.Width(), e.Height());
    }
  );
  WindowResizeTrigger.fire({5, 12});
  while(true);
}

Bandolier::AppPtr Bandolier::CreateApplication()
{
  return std::make_unique<Sandbox>();
}

