#pragma once

#include "Physics.hpp"
#include <vector>

class Simulation {
public:
    Simulation();

    void update(double dt);
    void reset();

    void addBody(Vector2 position);

    std::vector<Body>& getBodies() {
        return bodies;
    }

    Physics& getPhysics() {
        return physics;
    }

private:
    std::vector<Body> bodies;
    Physics physics;
};
