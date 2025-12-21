#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "vector.hpp"

#include <SDL3/SDL.h>

namespace game {

class Object2D {
public:
    Vector2D vel;
    Vector2D acc;
    Vector2D pos;

    Object2D(Vector2D pos);
    virtual ~Object2D() = default;

    virtual void update(float dt) noexcept final;
    virtual void render(SDL_Renderer* renderer) const noexcept = 0;

    [[nodiscard]] virtual float top_y() const noexcept = 0;
    [[nodiscard]] virtual float bottom_y() const noexcept = 0;
    [[nodiscard]] virtual float left_x() const noexcept = 0;
    [[nodiscard]] virtual float right_x() const noexcept = 0;
};

} // namespace game

#endif // OBJECT_HPP
