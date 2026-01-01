#include "object.h"

namespace game::objects {

Object2D::Object2D(Vector2D pos) noexcept
    : m_pos{pos} {}

void Object2D::update(float dt) noexcept {
    m_pos += m_vel * dt;
    m_vel += m_acc * dt;
    m_angle += m_ang_vel * dt;
}

[[nodiscard]] Vector2D Object2D::pos() const noexcept {
    return m_pos;
}

void Object2D::pos(Vector2D pos) noexcept {
    m_pos = pos;
}

[[nodiscard]] Vector2D Object2D::vel() const noexcept {
    return m_vel;
}

void Object2D::vel(Vector2D vel) noexcept {
    m_vel = vel;
}

[[nodiscard]] Vector2D Object2D::acc() const noexcept {
    return m_acc;
}

void Object2D::acc(Vector2D acc) noexcept {
    m_acc = acc;
}

[[nodiscard]] Color Object2D::color() const noexcept {
    return m_color;
}

void Object2D::color(Color color) noexcept {
    m_color = color;
}

[[nodiscard]] float Object2D::ang_vel() const noexcept {
    return m_ang_vel;
}

void Object2D::ang_vel(float ang_vel) noexcept {
    m_ang_vel = ang_vel;
}

} // namespace game::objects
