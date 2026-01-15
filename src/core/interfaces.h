#ifndef CORE_INTERFACES_H
#define CORE_INTERFACES_H

#include "core/math.h"
#include "core/renderer.h"

#include <array>

namespace game::core {

class IPhysical {
public:
    virtual ~IPhysical() = default;

    virtual void integrate(float dt) noexcept = 0;

    [[nodiscard]] virtual Vec2 get_pos() const noexcept = 0;
    virtual void set_pos(Vec2 pos) noexcept = 0;

    [[nodiscard]] virtual Vec2 get_vel() const noexcept = 0;
    virtual void set_vel(Vec2 vel) noexcept = 0;

    [[nodiscard]] virtual Vec2 get_acc() const noexcept = 0;
    virtual void set_acc(Vec2 acc) noexcept = 0;

    [[nodiscard]] virtual float get_rot_angle() const noexcept = 0;
    virtual void set_rot_angle(float angle) noexcept = 0;

    [[nodiscard]] virtual float get_ang_vel() const noexcept = 0;
    virtual void set_ang_vel(float ang_vel) noexcept = 0;
};

class IRenderable {
public:
    virtual ~IRenderable() = default;

    virtual void render(IRenderer& renderer) const noexcept = 0;

    [[nodiscard]] virtual Color get_color() const noexcept = 0;
    virtual void set_color(Color color) noexcept = 0;
};

} // namespace game::core

#endif // CORE_INTERFACES_H
