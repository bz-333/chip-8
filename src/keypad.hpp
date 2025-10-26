#pragma once

#include <array>
#include <cstdint>
#include <optional>

constexpr int NUM_KEYS = 16;

class Keypad {
public:
    void press(std::uint8_t key);
    void release(std::uint8_t key);
    bool is_pressed(std::uint8_t key);
    std::optional<std::uint8_t> get_pressed();
private:
    std::array<bool, NUM_KEYS> keys{};
};