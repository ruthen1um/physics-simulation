#include "object.hpp"

#include "vector.hpp"

namespace game {

Object2D::Object2D(const Vector2D& pos, float mass): pos{pos}, mass{mass} {}

void Object2D::update(const float dt) noexcept {
    pos += vel * dt;
    vel += acc * dt;
}

} // namespace game
