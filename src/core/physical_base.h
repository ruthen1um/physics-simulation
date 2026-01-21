#ifndef CORE_PHYSICAL_BASE_H
#define CORE_PHYSICAL_BASE_H

#include <memory>

#include "core/physical.h"
#include "core/vector.h"

namespace game::core {

class PhysicalBase : IPhysical {
public:
    PhysicalBase() = delete;
    ~PhysicalBase() noexcept override = default;

    PhysicalBase(const PhysicalBase&) noexcept = default;
    PhysicalBase& operator=(const PhysicalBase&) noexcept = default;

    PhysicalBase(PhysicalBase&&) noexcept = default;
    PhysicalBase& operator=(PhysicalBase&&) noexcept = default;

    explicit PhysicalBase(Vec2 pos) noexcept;

    void integrate(float dt) noexcept override;

    [[nodiscard]] Vec2 get_pos() const noexcept override;
    void set_pos(Vec2 pos) noexcept override;

    [[nodiscard]] Vec2 get_vel() const noexcept override;
    void set_vel(Vec2 vel) noexcept override;

    [[nodiscard]] Vec2 get_acc() const noexcept override;
    void set_acc(Vec2 acc) noexcept override;

    [[nodiscard]] float get_rot_angle() const noexcept override;
    void set_rot_angle(float angle) noexcept override;

    [[nodiscard]] float get_ang_vel() const noexcept override;
    void set_ang_vel(float ang_vel) noexcept override;

private:
    Vec2 m_pos;
    Vec2 m_vel{0.0f, 0.0f};
    Vec2 m_acc{0.0f, 0.0f};
    float m_rot_ang{0.0f};
    float m_ang_vel{0.0f};
};

} // namespace game::core

#endif // CORE_PHYSICAL_BASE_H
