#include "Body.hpp"

Body::Body(
    Vector2 position,
    Vector2 velocity,
    double mass,
    double radius,
    Color color
)
    : position(position),
      velocity(velocity),
      mass(mass),
      radius(radius),
      color(color)
{}
