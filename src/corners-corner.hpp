#pragma once

#include <peel/Gdk/Gdk.h>
#include <peel/Gsk/Gsk.h>
#include <peel/Gtk/Gtk.h>
#include <peel/class.h>
#include <peel/enum.h>

using namespace peel;

namespace Corners
{
enum class Position
{
  TOP_LEFT,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_RIGHT
};
} // namespace Corners

PEEL_ENUM (Corners::Position)

namespace Corners
{

class Corner final : public peel::GObject::Object
{
  PEEL_SIMPLE_CLASS (Corner, peel::GObject::Object);
  friend class peel::GObject::Object;
  friend class Gdk::Paintable;

  static void
  init_type (Type tp)
  {
    PEEL_IMPLEMENT_INTERFACE (tp, Gdk::Paintable);
  }

  static void
  init_interface (Gdk::Paintable::Iface *iface)
  {
    iface->override_vfunc_get_intrinsic_width<Corner> ();
    iface->override_vfunc_get_intrinsic_height<Corner> ();
    iface->override_vfunc_snapshot<Corner> ();
  }
  unsigned radius;
  Position position;

  template <typename F>
  static void
  define_properties (F &f)
  {
    f.prop (prop_radius (), 0, G_MAXUINT, 128).get (&Corner::get_radius);
    f.prop (prop_position (), Position::TOP_LEFT)
      .get (&Corner::get_position)
      .set (&Corner::set_position);
  }

  void init (Class *);

  void set_position (Position new_pos);

public:
  int
  vfunc_get_intrinsic_width ()
  {
    return (int)radius;
  };

  int
  vfunc_get_intrinsic_height ()
  {
    return (int)radius;
  };

  void vfunc_snapshot (Gdk::Snapshot *snapshot, double width, double height);

  unsigned
  get_radius ()
  {
    return radius;
  }

  PEEL_PROPERTY (unsigned, radius, "radius")

  Position
  get_position ()
  {
    return position;
  }

  PEEL_PROPERTY (Position, position, "position")

  static RefPtr<Corner>
  create (Position position)
  {
    return Object::create<Corner> (prop_position (), position);
  }
};
} // namespace Corners