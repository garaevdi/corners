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

  Gtk::Picture *top_left;
  Gtk::Picture *top_right;
  Gtk::Picture *bottom_left;
  Gtk::Picture *bottom_right;

  inline void init (Class *);

  inline void vfunc_dispose ();

public:
  static Window *
  create (Gtk::Application *app)
  {
    return Object::create<Window> (prop_application (), app);
  }
};
} // namespace Corners