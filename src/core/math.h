#ifndef CORE_VEC2_H
#define CORE_VEC2_H

#include <gcem.hpp>

namespace game::core {

constexpr auto PI = 3.14159265358979323846f;

struct Vec2 {
    float x;
    float y;

    constexpr Vec2() noexcept
        : x{0.0f}, y{0.0f} {}
    constexpr Vec2(float x, float y) noexcept
        : x{x}, y{y} {}
};

[[nodiscard]] constexpr Vec2 rotate(const Vec2& v, float angle) noexcept {
    return {
        v.x * gcem::cos(angle) + v.y * gcem::sin(angle),
        v.x * -gcem::sin(angle) + v.y * gcem::cos(angle),
    };
}

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

#endif // CORE_VEC2_H
