#include "corners-corner.hpp"

PEEL_ENUM_IMPL (Corners::Position, "CornersPosition",
  PEEL_ENUM_VALUE (Corners::Position::TOP_LEFT, "top_left"),
  PEEL_ENUM_VALUE (Corners::Position::TOP_RIGHT, "top_right"),
  PEEL_ENUM_VALUE (Corners::Position::BOTTOM_LEFT, "bottom_left"),
  PEEL_ENUM_VALUE (Corners::Position::BOTTOM_RIGHT, "bottom_right"))

namespace Corners
{
PEEL_CLASS_IMPL (Corner, "CornersCorner", peel::GObject::Object)

inline void
Corner::Class::init ()
{
}

void
Corner::init (Class *)
{
  radius = 15;
}

void
Corner::set_position (Position new_pos)
{
  position = new_pos;
  notify (prop_position ());
}

void
Corner::vfunc_snapshot (Gdk::Snapshot *snapshot, double width, double height)
{
  auto gtk_snapshot = (Gtk::Snapshot *)snapshot;
  auto builder = Gsk::PathBuilder::create ();
  switch (position)
    {
    case Position::TOP_LEFT:
      builder->line_to (0, radius);
      builder->arc_to (0, 0, radius, 0);
      builder->close ();
      break;
    case Position::TOP_RIGHT:
      builder->arc_to (radius, 0, radius, radius);
      builder->line_to (radius, 0);
      builder->close ();
      break;
    case Position::BOTTOM_LEFT:
      builder->arc_to (0, radius, radius, radius);
      builder->line_to (0, radius);
      builder->close ();
      break;
    case Position::BOTTOM_RIGHT:
      builder->move_to (radius, 0);
      builder->arc_to (radius, radius, 0, radius);
      builder->line_to (radius, radius);
      builder->close ();
      break;
    }
  auto path = builder->to_path ();
  gtk_snapshot->push_fill (path, Gsk::FillRule::WINDING_);
  auto color = new Gdk::RGBA{ 0, 0, 0, 1 };
  auto rect = new Graphene::Rect{ { 0, 0 },
    { static_cast<float> (radius), static_cast<float> (radius) } };
  gtk_snapshot->append_color (color, rect);
  gtk_snapshot->pop ();
}
} // namespace Corners