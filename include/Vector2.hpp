#pragma once

#include <cmath>

struct Vector2 {
    double x = 0.0;
    double y = 0.0;

    Vector2 operator+(const Vector2& v) const {
        return {x + v.x, y + v.y};
    }

    Vector2 operator-(const Vector2& v) const {
        return {x - v.x, y - v.y};
    }

    Vector2 operator*(double s) const {
        return {x * s, y * s};
    }

    Vector2 operator/(double s) const {
        return {x / s, y / s};
    }

    Vector2& operator+=(const Vector2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    double lengthSquared() const {
        return x * x + y * y;
    }

    double length() const {
        return std::sqrt(lengthSquared());
    }

    Vector2 normalized() const {
        double len = length();
        if (len < 1e-12) return {};
        return *this / len;
    }
};
