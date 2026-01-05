#ifndef CORE_COLOR_H
#define CORE_COLOR_H

#include <cstdint>

namespace game::core {

struct Color {
    uint8_t r{0xff};
    uint8_t g{0xff};
    uint8_t b{0xff};
    uint8_t a{0xff};

    constexpr Color() noexcept = default;
    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
        : r{r}, g{g}, b{b}, a{a} {};
};

} // namespace game::core

#endif // CORE_COLOR_H
