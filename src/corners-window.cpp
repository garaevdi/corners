#include "corners-window.hpp"

#include "config.h"

namespace Corners {
PEEL_CLASS_IMPL(Window, "CornersWindow", Gtk::ApplicationWindow)

inline void Window::Class::init() {
  override_vfunc_dispose<Window>();
  set_template_from_resource(APP_PATH "/ui/corners-window.ui");
}

inline void Window::init(Class *) { init_template(); }

inline void Window::vfunc_dispose() {
  dispose_template(Type::of<Window>());
  parent_vfunc_dispose<Window>();
}
} // namespace Corners