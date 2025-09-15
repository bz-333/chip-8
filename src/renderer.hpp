#include <SDL2/SDL.h>
#include <array>
#include <cstdint>

constexpr int CHIP8_WIDTH  = 64;
constexpr int CHIP8_HEIGHT = 32;
constexpr int PIXEL_SCALE  = 10;

class Renderer {
public:
    Renderer(const char* title);
    ~Renderer();

    void render(const std::array<uint8_t, CHIP8_WIDTH * CHIP8_HEIGHT>& display);
    void clear();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
