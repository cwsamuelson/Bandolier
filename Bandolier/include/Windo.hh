/* The file name "Windo" is not an accident
 * For some reason CLION would not do proper syntax highlighting in a file named Window.hh
 * Naming the file Windo.hh is a small work around for that.
 */

#ifndef TEST_WINDO_HH
#define TEST_WINDO_HH

#include <string>

#include <event_handler.hh>

#include "events.hh"
#include "ApplicationEvent.hh"

namespace Bandolier {

struct WindowProperties
{
  std::string title;
  unsigned int width;
  unsigned int height;
  bool vsync;

  WindowProperties(const std::string& intitle, unsigned int inwidth, unsigned int inheight, bool invsync = true)
    : title(intitle)
    , width(inwidth)
    , height(inheight)
    , vsync(invsync)
  {}
};

class Window
{
public:
  using Handler_t = gsw::event_trigger<Events::ApplicationEvent>::channel_t::simple_handler;

  virtual ~Window() = default;

  virtual void OnUpdate() = 0;

  virtual unsigned int
  Width() const = 0;
  virtual unsigned int
  Height() const = 0;

  virtual bool
  VSync() const = 0;
  virtual void
  VSync(bool enabled) = 0;
};

}

#endif //TEST_WINDO_HH
