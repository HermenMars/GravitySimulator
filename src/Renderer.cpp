#include "Renderer.hpp"

#include <cmath>

Renderer::Renderer(int width, int height) {
    window = SDL_CreateWindow(
        "2D Gravity Simulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!window) return;

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_SOFTWARE
        );
    }
}

Renderer::~Renderer() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
}

bool Renderer::isValid() const {
    return window && renderer;
}

void Renderer::drawCircle(
    int centerX,
    int centerY,
    int radius,
    Color color
) {
    SDL_SetRenderDrawColor(
        renderer,
        color.r,
        color.g,
        color.b,
        255
    );

    // Filled circle using horizontal scanlines.
    for (int y = -radius; y <= radius; ++y) {
        int x = static_cast<int>(
            std::sqrt(
                std::max(0, radius * radius - y * y)
            )
        );

        SDL_RenderDrawLine(
            renderer,
            centerX - x,
            centerY + y,
            centerX + x,
            centerY + y
        );
    }
}

void Renderer::draw(const std::vector<Body>& bodies) {
    SDL_SetRenderDrawColor(renderer, 12, 15, 25, 255);
    SDL_RenderClear(renderer);

    for (const Body& body : bodies) {
        drawCircle(
            static_cast<int>(body.position.x),
            static_cast<int>(body.position.y),
            static_cast<int>(body.radius),
            body.color
        );
    }

    SDL_RenderPresent(renderer);
}
