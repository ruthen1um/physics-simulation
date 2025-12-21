#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace game {

class Vector2D {
public:
    float x;
    float y;

    constexpr explicit Vector2D() noexcept
        : x{0.0f}, y{0.0f} {}
    constexpr explicit Vector2D(float x, float y) noexcept
        : x{x}, y{y} {}
};

[[nodiscard]] constexpr Vector2D operator+(const Vector2D& v1, const Vector2D& v2) noexcept {
    return Vector2D{v1.x + v2.x, v1.y + v2.y};
}

constexpr Vector2D& operator+=(Vector2D& v1, const Vector2D& v2) noexcept {
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

[[nodiscard]] constexpr Vector2D operator*(const Vector2D& v, float scalar) noexcept {
    return Vector2D{v.x * scalar, v.y * scalar};
}

constexpr Vector2D& operator*=(Vector2D& v1, float scalar) noexcept {
    v1.x *= scalar;
    v1.y *= scalar;
    return v1;
}

[[nodiscard]] constexpr Vector2D operator-(const Vector2D& v) noexcept {
    return Vector2D{-v.x, -v.y};
}

} // namespace game

#endif // VECTOR_HPP
