#include "corners-application.hpp"
#include "corners-window.hpp"

namespace Corners {
PEEL_CLASS_IMPL(Application, "CornersApplication", Gtk::Application)

inline void Application::Class::init() {
  override_vfunc_activate<Application>();
}

inline void Application::vfunc_activate() {
  parent_vfunc_activate<Application>();
  Window *window = Window::create(this);
  window->present();
}
} // namespace Corners

int main(int argc, char *argv[]) {
  RefPtr<Corners::Application> app = Corners::Application::create();
  return app->run(argc, argv);
}