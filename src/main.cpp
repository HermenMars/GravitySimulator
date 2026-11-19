#include "Simulation.hpp"
#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>

int main() {
    constexpr int WIDTH = 1200;
    constexpr int HEIGHT = 800;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: "
                  << SDL_GetError() << '\n';
        return 1;
    }

    Renderer renderer(WIDTH, HEIGHT);

    if (!renderer.isValid()) {
        std::cerr << "Renderer initialization failed: "
                  << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    Simulation simulation;

    bool running = true;
    bool paused = false;

    Uint64 previous = SDL_GetPerformanceCounter();

    std::cout << "2D Gravity Simulator\n"
              << "SPACE: Pause/resume\n"
              << "R: Reset\n"
              << "+/-: Change gravity\n"
              << "LEFT CLICK: Add a body\n"
              << "ESC: Quit\n";

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;

                    case SDLK_SPACE:
                        paused = !paused;
                        break;

                    case SDLK_r:
                        simulation.reset();
                        break;

                    case SDLK_PLUS:
                    case SDLK_EQUALS:
                    case SDLK_KP_PLUS:
                        simulation.getPhysics().gravitationalConstant *= 1.2;
                        break;

                    case SDLK_MINUS:
                    case SDLK_KP_MINUS:
                        simulation.getPhysics().gravitationalConstant /= 1.2;
                        break;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN &&
                event.button.button == SDL_BUTTON_LEFT) {

                simulation.addBody({
                    static_cast<double>(event.button.x),
                    static_cast<double>(event.button.y)
                });
            }
        }

        Uint64 current = SDL_GetPerformanceCounter();

        double dt =
            static_cast<double>(current - previous) /
            SDL_GetPerformanceFrequency();

        previous = current;

        // Prevent large jumps after window dragging or pauses.
        dt = std::min(dt, 0.033);

        if (!paused) {
            simulation.update(dt);
        }

        renderer.draw(simulation.getBodies());

        SDL_Delay(1);
    }

    SDL_Quit();
    return 0;
}
