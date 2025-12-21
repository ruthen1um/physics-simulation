#include "object.hpp"

#include "vector.hpp"

namespace game {

Object2D::Object2D(Vector2D pos): pos{pos} {}

void Object2D::update(float dt) noexcept {
    pos += vel * dt;
    vel += acc * dt;
}

} // namespace game
