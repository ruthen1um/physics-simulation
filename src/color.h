#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace game {

class Color {
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Color() noexcept;
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept;
};

} // namespace game

#endif // COLOR_H
