#pragma once

#include "Vector2.hpp"
#include <cstdint>

struct Color {
    std::uint8_t r, g, b;
};

class Body {
public:
    Vector2 position;
    Vector2 velocity;

    double mass;
    double radius;

    Color color;

    Body(
        Vector2 position,
        Vector2 velocity,
        double mass,
        double radius,
        Color color
    );
};
