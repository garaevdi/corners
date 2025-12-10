#include "corners-application.hpp"

#include "corners-window.hpp"

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
  monitors = display->get_monitors ();
  create_windows ();
  monitors->connect_items_changed (this, &Application::update_corners);
  hold ();
}

void
Application::update_corners (Gio::ListModel *, unsigned, unsigned, unsigned)
{
  auto windows = get_windows ();
  windows->foreach (
    windows, [] (void *window) { ((Window *)window)->close (); });

  Application::create_windows ();
}

void
Application::create_windows ()
{
  for (unsigned i = 0; i < monitors->get_n_items (); i++)
    {
      auto monitor = monitors->get_item (i);
      auto window = Window::create (this, (Gdk::Monitor *)monitor);
      window->present ();
    }
}
} // namespace Corners

int
main (int argc, char *argv[])
{
  RefPtr<Corners::Application> app = Corners::Application::create ();
  return app->run (argc, argv);
}