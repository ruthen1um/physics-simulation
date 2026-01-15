#ifndef CORE_PHYSICAL_BASE
#define CORE_PHYSICAL_BASE

#include "core/interfaces.h"

namespace game::core {

class PhysicalBase : IPhysical {
public:
    PhysicalBase() = delete;

    ~PhysicalBase() noexcept = default;

    constexpr PhysicalBase(const PhysicalBase&) noexcept = default;
    PhysicalBase& operator=(const PhysicalBase&) noexcept = default;

    constexpr PhysicalBase(PhysicalBase&&) noexcept = default;
    PhysicalBase& operator=(PhysicalBase&&) noexcept = default;

    constexpr PhysicalBase(Vec2 pos)
        : m_pos{pos} {};

    void integrate(float dt) noexcept override {
        m_pos += m_vel * dt;
        m_vel += m_acc * dt;
        m_rot_ang += m_ang_vel * dt;
    }

    [[nodiscard]] Vec2 get_pos() const noexcept override {
        return m_pos;
    };

    void set_pos(Vec2 pos) noexcept override {
        m_pos = pos;
    };

    [[nodiscard]] Vec2 get_vel() const noexcept override {
        return m_vel;
    }

    void set_vel(Vec2 vel) noexcept override {
        m_vel = vel;
    }

    [[nodiscard]] Vec2 get_acc() const noexcept override {
        return m_acc;
    }

    void set_acc(Vec2 acc) noexcept override {
        m_acc = acc;
    }

    [[nodiscard]] float get_rot_angle() const noexcept override {
        return m_rot_ang;
    }

    void set_rot_angle(float angle) noexcept override {
        m_rot_ang = angle;
    }

    [[nodiscard]] float get_ang_vel() const noexcept override {
        return m_ang_vel;
    }

    void set_ang_vel(float ang_vel) noexcept override {
        m_ang_vel = ang_vel;
    }

private:
    core::Vec2 m_pos{0.0f, 0.0f};
    core::Vec2 m_vel{0.0f, 0.0f};
    core::Vec2 m_acc{0.0f, 0.0f};
    float m_rot_ang{0.0f};
    float m_ang_vel{0.0f};
};

} // namespace game::core

#endif // CORE_PHYSICAL_BASE
