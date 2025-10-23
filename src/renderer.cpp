#include "constants.hpp"
#include "renderer.hpp"

Renderer::Renderer(const char* title) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              constants::DISPLAY_WIDTH * PIXEL_SCALE,
                              constants::DISPLAY_HEIGHT * PIXEL_SCALE,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::render(const std::array<uint8_t, constants::DISPLAY_WIDTH * constants::DISPLAY_HEIGHT>& display) {
    clear();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int y = 0; y < constants::DISPLAY_HEIGHT; ++y) {
        for (int x = 0; x < constants::DISPLAY_WIDTH; ++x) {
            if (display[x + y * constants::DISPLAY_WIDTH]) {
                SDL_Rect rect = { x * PIXEL_SCALE, y * PIXEL_SCALE, PIXEL_SCALE, PIXEL_SCALE };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}
