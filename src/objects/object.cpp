#include "object.h"
#include "../core/color.h"
#include "../core/vec.h"

using game::core::Color;
using game::core::Vec2;

namespace game::objects {

Object2::Object2(Vec2 pos) noexcept
    : m_pos{pos} {}

void Object2::update(float dt) noexcept {
    m_pos += m_vel * dt;
    m_vel += m_acc * dt;
    m_angle += m_ang_vel * dt;
}

[[nodiscard]] Vec2 Object2::pos() const noexcept {
    return m_pos;
}

void Object2::pos(Vec2 pos) noexcept {
    m_pos = pos;
}

[[nodiscard]] Vec2 Object2::vel() const noexcept {
    return m_vel;
}

void Object2::vel(Vec2 vel) noexcept {
    m_vel = vel;
}

[[nodiscard]] Vec2 Object2::acc() const noexcept {
    return m_acc;
}

void Object2::acc(Vec2 acc) noexcept {
    m_acc = acc;
}

[[nodiscard]] Color Object2::color() const noexcept {
    return m_color;
}

void Object2::color(Color color) noexcept {
    m_color = color;
}

[[nodiscard]] float Object2::ang_vel() const noexcept {
    return m_ang_vel;
}

void Object2::ang_vel(float ang_vel) noexcept {
    m_ang_vel = ang_vel;
}

} // namespace game::objects
