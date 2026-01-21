#include "core/physical_base.h"

#include <utility>

namespace game::core {

PhysicalBase::PhysicalBase(core::Vec2 pos) noexcept
    : m_pos{std::move(pos)} {}

void PhysicalBase::integrate(float dt) noexcept {
    m_pos += m_vel * dt;
    m_vel += m_acc * dt;
    m_rot_ang += m_ang_vel * dt;
}

[[nodiscard]] Vec2 PhysicalBase::get_pos() const noexcept {
    return m_pos;
};

void PhysicalBase::set_pos(Vec2 pos) noexcept {
    m_pos = pos;
};

[[nodiscard]] Vec2 PhysicalBase::get_vel() const noexcept {
    return m_vel;
}

void PhysicalBase::set_vel(Vec2 vel) noexcept {
    m_vel = vel;
}

[[nodiscard]] Vec2 PhysicalBase::get_acc() const noexcept {
    return m_acc;
}

void PhysicalBase::set_acc(Vec2 acc) noexcept {
    m_acc = acc;
}

[[nodiscard]] float PhysicalBase::get_rot_angle() const noexcept {
    return m_rot_ang;
}

void PhysicalBase::set_rot_angle(float angle) noexcept {
    m_rot_ang = angle;
}

[[nodiscard]] float PhysicalBase::get_ang_vel() const noexcept {
    return m_ang_vel;
}

void PhysicalBase::set_ang_vel(float ang_vel) noexcept {
    m_ang_vel = ang_vel;
}

} // namespace game::core
