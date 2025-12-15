#include "corners-window.hpp"

#include "config.h"
#include "corners-corner.hpp"

#include <cairo.h>
#include <peel/Gdk/Surface.h>
#include <peel/Gtk4LayerShell/Gtk4LayerShell.h>
#include <peel/widget-template.h>

namespace Corners
{
PEEL_CLASS_IMPL (Window, "CornersWindow", Gtk::Window)

inline void
Window::Class::init ()
{
  override_vfunc_dispose<Window> ();
  set_template_from_resource (APP_PATH "/ui/corners-window.ui");
  PEEL_WIDGET_TEMPLATE_BIND_CHILD (Window, top_left);
  PEEL_WIDGET_TEMPLATE_BIND_CHILD (Window, top_right);
  PEEL_WIDGET_TEMPLATE_BIND_CHILD (Window, bottom_left);
  PEEL_WIDGET_TEMPLATE_BIND_CHILD (Window, bottom_right);
}

inline void
Window::init (Class *)
{
  init_template ();
  Gtk4LayerShell::init_for_window (this);
  Gtk4LayerShell::set_monitor (this, monitor);
  Gtk4LayerShell::set_anchor (this, Gtk4LayerShell::Edge::TOP, true);
  Gtk4LayerShell::set_anchor (this, Gtk4LayerShell::Edge::LEFT, true);
  Gtk4LayerShell::set_anchor (this, Gtk4LayerShell::Edge::RIGHT, true);
  Gtk4LayerShell::set_anchor (this, Gtk4LayerShell::Edge::BOTTOM, true);
  this->remove_css_class ("background");
  this->connect_map ([] (Gtk::Widget *widget) {
    auto window = (Window *)widget;
    auto *surface = window->get_surface ();
    auto rect = cairo_rectangle_int_t{ 0, 0, 0, 0 };
    surface->set_input_region (cairo_region_create_rectangle (&rect));
  });
  auto top_left_corner = Corner::create (Position::TOP_LEFT);
  top_left->set_paintable (top_left_corner->cast<Gdk::Paintable> ());
  auto top_right_corner = Corner::create (Position::TOP_RIGHT);
  top_right->set_paintable (top_right_corner->cast<Gdk::Paintable> ());
  auto bottom_right_corner = Corner::create (Position::BOTTOM_RIGHT);
  bottom_right->set_paintable (bottom_right_corner->cast<Gdk::Paintable> ());
  auto bottom_left_corner = Corner::create (Position::BOTTOM_LEFT);
  bottom_left->set_paintable (bottom_left_corner->cast<Gdk::Paintable> ());
}

void
Window::set_monitor (Gdk::Monitor *new_monitor)
{
  if (monitor == new_monitor)
    return;

  monitor = new_monitor;
  notify (prop_monitor ());
  Gtk4LayerShell::set_monitor (this, monitor);
}

inline void
Window::vfunc_dispose ()
{
  dispose_template (Type::of<Window> ());
  parent_vfunc_dispose<Window> ();
}
} // namespace Corners
