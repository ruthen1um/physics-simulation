#include "color.h"

#include <cstdint>

namespace game {

Color::Color() noexcept
    : r{0xff}, g{0xff}, b{0xff}, a{0xff} {}

Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) noexcept
    : r{r}, g{g}, b{b}, a{a} {}

} // namespace game
