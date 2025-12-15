#pragma once

#include <peel/Gtk/Gtk.h>
#include <peel/class.h>

using namespace peel;

namespace Corners
{
class Window final : public Gtk::Window
{
  PEEL_SIMPLE_CLASS (Window, Gtk::Window);
  friend class Gtk::Window;

  RefPtr<Gdk::Monitor> monitor;

  template <typename F>
  static void
  define_properties (F &f)
  {
    f.prop (prop_monitor ())
      .get (&Window::get_monitor)
      .set (&Window::set_monitor);
  }

  Gtk::Picture *top_left;
  Gtk::Picture *top_right;
  Gtk::Picture *bottom_left;
  Gtk::Picture *bottom_right;

  inline void
  init (Class *);

  inline void
  vfunc_dispose ();

  void
  set_monitor (Gdk::Monitor *new_monitor);

public:
  Gdk::Monitor *
  get_monitor ()
  {
    return monitor;
  }

  PEEL_PROPERTY (Gdk::Monitor, monitor, "monitor")

  static Window *
  create (Gtk::Application *app, Gdk::Monitor *monitor)
  {
    return Object::create<Window> (
      prop_application (), app, prop_monitor (), monitor);
  }
};
} // namespace Corners
