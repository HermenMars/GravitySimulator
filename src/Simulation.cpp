#include "Simulation.hpp"

#include <random>
#include <cmath>

Simulation::Simulation() {
    reset();
}

void Simulation::reset() {
    bodies.clear();

    // Large central body.
    bodies.emplace_back(
        Vector2{600, 400},
        Vector2{0, 0},
        1200.0,
        25.0,
        Color{255, 210, 80}
    );

    // Orbiting bodies.
    bodies.emplace_back(
        Vector2{600, 220},
        Vector2{85, 0},
        12.0,
        10.0,
        Color{80, 170, 255}
    );

    bodies.emplace_back(
        Vector2{600, 90},
        Vector2{68, 0},
        8.0,
        7.0,
        Color{255, 100, 100}
    );

    bodies.emplace_back(
        Vector2{850, 400},
        Vector2{0, 65},
        25.0,
        14.0,
        Color{100, 255, 150}
    );

    bodies.emplace_back(
        Vector2{350, 400},
        Vector2{0, -90},
        18.0,
        12.0,
        Color{190, 120, 255}
    );

    bodies.emplace_back(
        Vector2{600, 550},
        Vector2{-75, 0},
        15.0,
        11.0,
        Color{255, 160, 70}
    );
}

void Simulation::update(double dt) {
    physics.update(bodies, dt);
}

void Simulation::addBody(Vector2 position) {
    static std::mt19937 rng(std::random_device{}());

    std::uniform_real_distribution<double> massDistribution(5, 40);
    std::uniform_real_distribution<double> radiusDistribution(5, 15);
    std::uniform_int_distribution<int> colorDistribution(80, 255);

    double mass = massDistribution(rng);
    double radius = radiusDistribution(rng);

    Color color{
        static_cast<std::uint8_t>(colorDistribution(rng)),
        static_cast<std::uint8_t>(colorDistribution(rng)),
        static_cast<std::uint8_t>(colorDistribution(rng))
    };

    bodies.emplace_back(
        position,
        Vector2{0, 0},
        mass,
        radius,
        color
    );
}
