#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "vector.hpp"
#include <SDL3/SDL.h>

namespace game {

class Object2D {
public:
    Vector2D pos;
    Vector2D vel;
    Vector2D acc;
    float mass;

    Object2D(const Vector2D& pos, float mass);
    virtual ~Object2D() = default;

    virtual void update(const float dt) noexcept final;
    virtual void render(SDL_Renderer* renderer) const noexcept = 0;

    [[nodiscard]] virtual float top() const noexcept = 0;
    [[nodiscard]] virtual float bottom() const noexcept = 0;
    [[nodiscard]] virtual float left() const noexcept = 0;
    [[nodiscard]] virtual float right() const noexcept = 0;
};

} // namespace game

#endif // OBJECT_HPP
