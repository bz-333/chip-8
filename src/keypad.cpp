#include "keypad.hpp"

void Keypad::press(std::uint8_t key) {
    if (key >= 16u) {
        return;
    }
    keys[key] = true;
}

void Keypad::release(std::uint8_t key) {
    if (key >= 16u) {
        return;
    }
    keys[key] = false;
}

bool Keypad::is_pressed(std::uint8_t key) {
    if (key >= 16u) {
        return false;
    }
    return keys[key];
}

std::optional<std::uint8_t> Keypad::get_pressed() {
    for (auto i = 0; i < NUM_KEYS; ++i) {
        if (keys[i]) {
            return i;
        }
    }
    return std::nullopt;
}