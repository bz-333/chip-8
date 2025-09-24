#include <cstdint>
#include <array>
#include <stack>
#include <filesystem>

const unsigned int MEMORY_SIZE = 4096;
const unsigned int DISPLAY_WIDTH = 64;
const unsigned int DISPLAY_HEIGHT = 32;
const unsigned int REGISTER_COUNT = 16;
const unsigned int FONT_SIZE = 80;

struct Emulator {
    std::array<std::uint8_t, MEMORY_SIZE> memory{};
    std::array<std::uint8_t, DISPLAY_WIDTH * DISPLAY_HEIGHT> display{};
    std::uint16_t pc{};
    std::uint16_t index{};
    std::stack<std::uint16_t> call_stack;
    std::uint8_t delay{};
    std::uint8_t sound{};
    std::array<std::uint8_t, REGISTER_COUNT> registers{};
    bool draw{};

    static constexpr std::array<uint8_t, FONT_SIZE> font{
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    Emulator();

    void load_rom(const std::filesystem::path& filename);

    void cycle();

    void decode_and_execute(std::uint16_t opcode);

    void op_00E0();

    void op_00EE();

    void op_1NNN(std::uint16_t NNN);

    void op_2NNN(std::uint16_t NNN);

    void op_3XNN(std::uint8_t X, std::uint8_t NN);

    void op_4XNN(std::uint8_t X, std::uint8_t NN);

    void op_5XY0(std::uint8_t X, std::uint8_t Y);

    void op_6XNN(std::uint8_t X, std::uint8_t NN);

    void op_7XNN(std::uint8_t X, std::uint8_t NN);

    void op_9XY0(std::uint8_t X, std::uint8_t Y);

    void op_ANNN(std::uint16_t NNN);

    void op_DXYN(std::uint8_t X, std::uint8_t Y, std::uint8_t N);

};