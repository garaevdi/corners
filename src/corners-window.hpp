#pragma once

#include <peel/Gtk/Gtk.h>
#include <peel/class.h>

using namespace peel;

namespace Corners {
class Window final : public Gtk::ApplicationWindow {
  PEEL_SIMPLE_CLASS(Window, Gtk::ApplicationWindow);

  inline void init(Class *);

  inline void vfunc_dispose();

public:
  static Window *create(Gtk::Application *app) {
    return Object::create<Window>(prop_application(), app);
  }
};
} // namespace Corners