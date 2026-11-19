#pragma once

#include "Body.hpp"
#include <vector>

class Physics {
public:
    double gravitationalConstant = 1000.0;
    double softening = 8.0;
    double restitution = 0.85;

    void update(std::vector<Body>& bodies, double dt);

private:
    void calculateGravity(
        std::vector<Body>& bodies,
        std::vector<Vector2>& accelerations
    );

    void resolveCollisions(std::vector<Body>& bodies);
};
