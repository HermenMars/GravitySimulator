#include "Physics.hpp"

#include <cmath>
#include <algorithm>

void Physics::calculateGravity(
    std::vector<Body>& bodies,
    std::vector<Vector2>& accelerations
) {
    const std::size_t count = bodies.size();

    accelerations.assign(count, {});

    // Every body attracts every other body.
    for (std::size_t i = 0; i < count; ++i) {
        for (std::size_t j = i + 1; j < count; ++j) {

            Vector2 delta =
                bodies[j].position - bodies[i].position;

            double distanceSquared =
                delta.lengthSquared() + softening * softening;

            double distance =
                std::sqrt(distanceSquared);

            double factor =
                gravitationalConstant /
                (distanceSquared * distance);

            // Acceleration of body i caused by body j.
            Vector2 accelerationI =
                delta * (factor * bodies[j].mass);

            // Acceleration of body j caused by body i.
            Vector2 accelerationJ =
                delta * (-factor * bodies[i].mass);

            accelerations[i] += accelerationI;
            accelerations[j] += accelerationJ;
        }
    }
}

void Physics::resolveCollisions(std::vector<Body>& bodies) {
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        for (std::size_t j = i + 1; j < bodies.size(); ++j) {

            Body& a = bodies[i];
            Body& b = bodies[j];

            Vector2 delta = b.position - a.position;

            double distance = delta.length();
            double minimumDistance = a.radius + b.radius;

            if (distance >= minimumDistance || distance < 1e-9)
                continue;

            Vector2 normal = delta / distance;

            double inverseMassA = 1.0 / a.mass;
            double inverseMassB = 1.0 / b.mass;

            double inverseMassSum =
                inverseMassA + inverseMassB;

            // Separate overlapping bodies.
            double penetration = minimumDistance - distance;

            Vector2 correction =
                normal * (penetration / inverseMassSum);

            a.position -= correction * inverseMassA;
            b.position += correction * inverseMassB;

            // Calculate collision impulse.
            Vector2 relativeVelocity =
                b.velocity - a.velocity;

            double velocityAlongNormal =
                relativeVelocity.x * normal.x +
                relativeVelocity.y * normal.y;

            if (velocityAlongNormal > 0.0)
                continue;

            double impulseMagnitude =
                -(1.0 + restitution) *
                velocityAlongNormal / inverseMassSum;

            Vector2 impulse =
                normal * impulseMagnitude;

            a.velocity -= impulse * inverseMassA;
            b.velocity += impulse * inverseMassB;
        }
    }
}

void Physics::update(std::vector<Body>& bodies, double dt) {
    if (dt <= 0.0) return;

    std::vector<Vector2> accelerations;

    // Semi-implicit Euler integration.
    // Substeps improve stability at higher speeds.
    constexpr int substeps = 4;
    const double step = dt / substeps;

    for (int s = 0; s < substeps; ++s) {
        calculateGravity(bodies, accelerations);

        for (std::size_t i = 0; i < bodies.size(); ++i) {
            bodies[i].velocity += accelerations[i] * step;
            bodies[i].position += bodies[i].velocity * step;
        }

        resolveCollisions(bodies);
    }
}
