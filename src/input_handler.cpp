#include "input_handler.hpp"

void InputHandler::process_input(Keypad& keypad) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            state = false;
        }
        
        if (event.type == SDL_KEYDOWN) {
            keypad.press(key_to_int(event.key.keysym.sym));
        }

        if (event.type == SDL_KEYUP) {
            keypad.release(key_to_int(event.key.keysym.sym));
        }
    }
}

InputHandler::operator bool() const {
    return state;
}

std::uint8_t InputHandler::key_to_int(SDL_Keycode key) {
    switch (key) {
        case SDLK_1:
            return 1u;
        case SDLK_2:
            return 2u;
        case SDLK_3:
            return 3u;
        case SDLK_4:
            return 12u;
        case SDLK_q:
            return 4u;
        case SDLK_w:
            return 5u;
        case SDLK_e:
            return 6u;
        case SDLK_r:
            return 13u;
        case SDLK_a:
            return 7u;
        case SDLK_s:
            return 8u;
        case SDLK_d:
            return 9u;
        case SDLK_f:
            return 14u;
        case SDLK_z:
            return 10u;
        case SDLK_x:
            return 0u;
        case SDLK_c:
            return 11u;
        case SDLK_v:
            return 15u;
    }
    return 0u;
}