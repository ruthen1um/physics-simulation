#include "objects/shape.h"

#include <utility>
#include <vector>

#include "core/color.h"
#include "core/vector.h"

namespace game::objects {

Shape::Shape(core::Vec2 pos, core::Color color) noexcept
    : m_physical{std::move(pos)}, m_renderable{std::move(color)} {}

void Shape::integrate(float dt) noexcept {
    m_physical.integrate(dt);
}

[[nodiscard]] core::Vec2 Shape::get_pos() const noexcept {
    return m_physical.get_pos();
}

void Shape::set_pos(core::Vec2 pos) noexcept {
    m_physical.set_pos(std::move(pos));
}

[[nodiscard]] core::Vec2 Shape::get_vel() const noexcept {
    return m_physical.get_vel();
}

void Shape::set_vel(core::Vec2 vel) noexcept {
    m_physical.set_vel(std::move(vel));
}

[[nodiscard]] core::Vec2 Shape::get_acc() const noexcept {
    return m_physical.get_acc();
}

void Shape::set_acc(core::Vec2 acc) noexcept {
    m_physical.set_acc(std::move(acc));
}

[[nodiscard]] float Shape::get_rot_angle() const noexcept {
    return m_physical.get_rot_angle();
}

void Shape::set_rot_angle(float angle) noexcept {
    m_physical.set_rot_angle(std::move(angle));
}

[[nodiscard]] float Shape::get_ang_vel() const noexcept {
    return m_physical.get_ang_vel();
}

void Shape::set_ang_vel(float ang_vel) noexcept {
    m_physical.set_ang_vel(std::move(ang_vel));
}

void Shape::render(core::IRenderer&) const noexcept {}

[[nodiscard]] core::Color Shape::get_color() const noexcept {
    return m_renderable.get_color();
}

void Shape::set_color(core::Color color) noexcept {
    m_renderable.set_color(std::move(color));
}

[[nodiscard]] std::vector<core::Vec2> Shape::get_vertices_world() const noexcept {
    return {};
}

} // namespace game::objects
