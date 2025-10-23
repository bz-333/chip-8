#include "emulator.hpp"
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "constants.hpp"

Emulator::Emulator() {
    pc = START_ADDRESS;

    std::copy(font.begin(), font.end(), memory.begin() + FONT_START_ADDRESS);
}

void Emulator::load_rom(const std::filesystem::path& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to load ROM!\n";
        throw std::runtime_error("Failed to open ROM file: " + filename.string());
    }

    std::size_t size = static_cast<std::size_t>(file.tellg());
    if (size > (memory.size() - START_ADDRESS)) {
        throw std::runtime_error("ROM size too large to fit in memory");
    }

    std::vector<std::uint8_t> buffer(size);
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(buffer.data()), size);

    std::copy(buffer.begin(), buffer.end(), memory.begin() + START_ADDRESS);
}

void Emulator::cycle() {
    if (pc >= memory.size()) {
        return;
    }

    std::uint16_t opcode = (memory[pc] << 8u) | memory[pc + 1];
    pc += 2;

    decode_and_execute(opcode);
}

void Emulator::decode_and_execute(std::uint16_t opcode) {
    std::uint8_t X = (opcode & 0x0F00u) >> 8u;
    std::uint8_t Y = (opcode & 0x00F0u) >> 4u;
    std::uint8_t N = (opcode & 0x000Fu);
    std::uint8_t NN = (opcode & 0x00FFu);
    std::uint16_t NNN = (opcode & 0x0FFFu);

    switch (opcode & 0xF000u) {
        case 0x0000u:
            switch (NN) {
                case 0xE0u:
                    op_00E0();
                    break;
                case 0xEEu:
                    break;
            }
            break;
        case 0x1000u:
            op_1NNN(NNN);
            break;
        case 0x2000u:
            op_2NNN(NNN);
            break;
        case 0x3000u:
            op_3XNN(X, NN);
            break;
        case 0x4000u:
            op_4XNN(X, NN);
            break;
        case 0x5000u:
            op_5XY0(X, Y);
            break;
        case 0x6000u:
            op_6XNN(X, NN);
            break;
        case 0x7000u:
            op_7XNN(X, NN);
            break;
        case 0x9000u:
            op_9XY0(X, Y);
            break;
        case 0xA000u:
            op_ANNN(NNN);
            break;
        case 0xD000u:
            op_DXYN(X, Y, N);
            break;
    }
}

const std::array<uint8_t, constants::DISPLAY_WIDTH * constants::DISPLAY_HEIGHT>& Emulator::get_display() {
    return display;
}

bool Emulator::should_draw() {
    return draw;
}

void Emulator::set_draw(bool should_draw) {
    draw = should_draw;
}

void Emulator::op_00E0() {
    std::fill(display.begin(), display.end(), 0);
}

void Emulator::op_00EE() {
    pc = call_stack.top();
    call_stack.pop();
}

void Emulator::op_1NNN(std::uint16_t NNN) {
    pc = NNN;
}

void Emulator::op_2NNN(std::uint16_t NNN) {
    call_stack.push(pc);
    pc = NNN;
}

void Emulator::op_3XNN(std::uint8_t X, std::uint8_t NN) {
    if (registers[X] == NN) {
        pc += 2;
    }
}

void Emulator::op_4XNN(std::uint8_t X, std::uint8_t NN) {
    if (registers[X] != NN) {
        pc += 2;
    }
}

void Emulator::op_5XY0(std::uint8_t X, std::uint8_t Y) {
    if (registers[X] == registers[Y]) {
        pc += 2;
    }
}

void Emulator::op_6XNN(std::uint8_t X, std::uint8_t NN) {
    registers[X] = NN;
}

void Emulator::op_7XNN(std::uint8_t X, std::uint8_t NN) {
    registers[X] += NN;
}

void Emulator::op_9XY0(std::uint8_t X, std::uint8_t Y) {
    if (registers[X] != registers[Y]) {
        pc += 2;
    }
}

void Emulator::op_ANNN(std::uint16_t NNN) {
    index = NNN;
}

void Emulator::op_DXYN(std::uint8_t X, std::uint8_t Y, std::uint8_t N) {
    const std::uint8_t x_coord = registers[X] % constants::DISPLAY_WIDTH;
    const std::uint8_t y_coord = registers[Y] % constants::DISPLAY_HEIGHT;

    registers[0xF] = 0u;

    for (std::uint8_t i = 0u; i < N && y_coord + i < constants::DISPLAY_HEIGHT; ++i) {
        const std::uint8_t sprite_row = memory[index + i];
        for (std::uint8_t j = 0u; j < 8u && x_coord + j < constants::DISPLAY_WIDTH; ++j) {
            if (!(sprite_row & (0x80 >> j))) {
                continue;
            }

            const std::uint16_t display_index = (constants::DISPLAY_WIDTH * (y_coord + i)) + (x_coord + j);
            if (display[display_index]) {
                display[display_index] = 0u;
                registers[0xF] = 1u;
            } else {
                display[display_index] = 1u;
            }

        }
    }

    draw = true;
}