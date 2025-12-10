#include "corners-application.hpp"

#include "corners-window.hpp"
#include "peel/Gtk4LayerShell/functions.h"

#include <peel/Gtk4LayerShell/Gtk4LayerShell.h>

namespace Corners
{
PEEL_CLASS_IMPL (Application, "CornersApplication", Gtk::Application)

inline void
Application::Class::init ()
{
  override_vfunc_activate<Application> ();
}

inline void
Application::vfunc_activate ()
{
  parent_vfunc_activate<Application> ();
  FloatPtr<Gdk::Display> display = Gdk::Display::get_default ();
  RefPtr<Gio::ListModel> monitors = display->get_monitors ();
  for (unsigned i = 0; i < monitors->get_n_items (); i++)
    {
      auto monitor = monitors->get_item (i);
      auto window = Window::create (this);
      window->present ();
      Gtk4LayerShell::set_monitor (window, (Gdk::Monitor *)monitor);
    }
  hold ();
}
} // namespace Corners

int
main (int argc, char *argv[])
{
  RefPtr<Corners::Application> app = Corners::Application::create ();
  return app->run (argc, argv);
}