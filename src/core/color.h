#ifndef CORE_COLOR_H
#define CORE_COLOR_H

#include <cstdint>

namespace game::core {

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    constexpr Color() noexcept = delete;
    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
        : r{r}, g{g}, b{b}, a{a} {};

    constexpr Color(const Color&) noexcept = default;
    constexpr Color& operator=(const Color&) noexcept = default;

    constexpr Color(Color&&) noexcept = default;
    constexpr Color& operator=(Color&&) noexcept = default;
};

} // namespace game::core

#endif // CORE_COLOR_H
