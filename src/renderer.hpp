#include <SDL2/SDL.h>
#include <array>
#include <cstdint>
#include "constants.hpp"

constexpr int PIXEL_SCALE  = 10;

class Renderer {
public:
    Renderer(const char* title);
    ~Renderer();

    void render(const std::array<uint8_t, constants::DISPLAY_WIDTH * constants::DISPLAY_HEIGHT>& display);
    void clear();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
