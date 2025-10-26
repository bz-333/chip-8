#pragma once

#include <SDL2/SDL.h>
#include "keypad.hpp"

class InputHandler {
public:
    void process_input(Keypad& keypad);
    operator bool() const;
private:
    bool state{true};

    std::uint8_t key_to_int(SDL_Keycode key);
};