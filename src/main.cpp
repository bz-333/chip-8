#include <SDL2/SDL.h>
#include "emulator.hpp"
#include "renderer.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    Emulator chip8;
    chip8.load_rom("roms/ibm-logo.ch8");

    Renderer renderer("CHIP-8");

    bool quit = false;
    SDL_Event e;
    const int cycles_per_frame = 10;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
            // TODO: map keyboard events to chip8 keys
        }

        chip8.cycle();

        if (chip8.draw) {
            for (auto i : chip8.display) {
                std::cout << static_cast<int>(i);
            }
            renderer.render(chip8.display);
            chip8.draw = false;
        }

        SDL_Delay(1);
    }

    return 0;
}