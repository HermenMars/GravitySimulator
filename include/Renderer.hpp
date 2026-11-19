#pragma once

#include "Body.hpp"
#include <SDL2/SDL.h>
#include <vector>

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();

    bool isValid() const;
    void draw(const std::vector<Body>& bodies);

private:
    void drawCircle(
        int centerX,
        int centerY,
        int radius,
        Color color
    );

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
