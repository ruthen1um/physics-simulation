#ifndef OBJECTS_OBJECT_H
#define OBJECTS_OBJECT_H

#include "../core/color.h"
#include "../core/vec.h"
#include "i_object.h"

namespace game::objects {

class Object2 : public IObject2 {
public:
    core::Vec2 m_pos;
    core::Vec2 m_vel;
    core::Vec2 m_acc;
    core::Color m_color;
    float m_angle{0.0f};
    float m_ang_vel{0.0f};

    Object2(core::Vec2 pos) noexcept;

    void update(float dt) noexcept override;

    [[nodiscard]] core::Vec2 pos() const noexcept;
    void pos(core::Vec2 pos) noexcept;

    [[nodiscard]] core::Vec2 vel() const noexcept;
    void vel(core::Vec2 vel) noexcept;

    [[nodiscard]] core::Vec2 acc() const noexcept;
    void acc(core::Vec2 acc) noexcept;

    [[nodiscard]] core::Color color() const noexcept;
    void color(core::Color color) noexcept;

    [[nodiscard]] float ang_vel() const noexcept;
    void ang_vel(float ang_vel) noexcept;
};

} // namespace game::objects

#endif // OBJECTS_OBJECT_H
