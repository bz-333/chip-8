#include <SDL2/SDL.h>
#include "emulator.hpp"
#include "renderer.hpp"
#include "input_handler.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    Emulator emulator;
    emulator.load_rom("roms/4-flags.ch8");

    Renderer renderer("CHIP-8");
    InputHandler input_handler;

    while (input_handler) {
        input_handler.process_input(emulator.get_keypad());

        emulator.cycle();

        if (emulator.should_draw()) {
            renderer.render(emulator.get_display());
            emulator.set_draw(false);
        }

        SDL_Delay(1);
    }

    return 0;
}