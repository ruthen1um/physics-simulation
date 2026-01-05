#ifndef CORE_VEC_H
#define CORE_VEC_H

#include <gcem.hpp>

namespace game::core {

struct Vec2 {
    float x;
    float y;

    constexpr Vec2() noexcept
        : x{0.0f}, y{0.0f} {}
    constexpr Vec2(float x, float y) noexcept
        : x{x}, y{y} {}
    [[nodiscard]] constexpr Vec2 rotate(float angle) const noexcept {
        return {
            x * gcem::cos(angle) + y * gcem::sin(angle),
            x * -gcem::sin(angle) + y * gcem::cos(angle),
        };
    }
};

[[nodiscard]] constexpr Vec2 operator+(const Vec2& v1, const Vec2& v2) noexcept {
    return {v1.x + v2.x, v1.y + v2.y};
}

constexpr Vec2& operator+=(Vec2& v1, const Vec2& v2) noexcept {
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

[[nodiscard]] constexpr Vec2 operator*(const Vec2& v, float scalar) noexcept {
    return {v.x * scalar, v.y * scalar};
}

constexpr Vec2& operator*=(Vec2& v1, float scalar) noexcept {
    v1.x *= scalar;
    v1.y *= scalar;
    return v1;
}

[[nodiscard]] constexpr Vec2 operator-(const Vec2& v) noexcept {
    return {-v.x, -v.y};
}

[[nodiscard]] constexpr Vec2 operator-(const Vec2& v1, const Vec2& v2) noexcept {
    return {v1.x - v2.x, v1.y - v2.y};
}

constexpr Vec2& operator-=(Vec2& v1, const Vec2& v2) noexcept {
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

} // namespace game::core

#endif // CORE_VEC_H
