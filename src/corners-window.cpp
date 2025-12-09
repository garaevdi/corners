#include "corners-window.hpp"

#include "config.h"

#include <cairo.h>
#include <peel/Gdk/Surface.h>
#include <peel/Gtk4LayerShell/Gtk4LayerShell.h>

namespace Corners {
PEEL_CLASS_IMPL(Window, "CornersWindow", Gtk::Window)

inline void Window::Class::init() {
  override_vfunc_dispose<Window>();
  set_template_from_resource(APP_PATH "/ui/corners-window.ui");
}

inline void Window::init(Class *) {
  init_template();
  Gtk4LayerShell::init_for_window(this);
  Gtk4LayerShell::set_anchor(this, Gtk4LayerShell::Edge::TOP, true);
  Gtk4LayerShell::set_anchor(this, Gtk4LayerShell::Edge::LEFT, true);
  Gtk4LayerShell::set_anchor(this, Gtk4LayerShell::Edge::RIGHT, true);
  Gtk4LayerShell::set_anchor(this, Gtk4LayerShell::Edge::BOTTOM, true);
  this->remove_css_class("background");
  this->connect_map([](Gtk::Widget *widget) {
    auto window = (Window *)widget;
    auto *surface = window->get_surface();
    auto rect = cairo_rectangle_int_t{0, 0, 0, 0};
    surface->set_input_region(cairo_region_create_rectangle(&rect));
  });
}

inline void Window::vfunc_dispose() {
  dispose_template(Type::of<Window>());
  parent_vfunc_dispose<Window>();
}
} // namespace Corners