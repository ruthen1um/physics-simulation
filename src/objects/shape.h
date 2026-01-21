#ifndef OBJECTS_SHAPE_H
#define OBJECTS_SHAPE_H

#include <cstddef>
#include <exception>
#include <memory>
#include <stdexcept>
#include <vector>

#include "core/collidable.h"
#include "core/collision.h"
#include "core/physical.h"
#include "core/physical_base.h"
#include "core/renderable.h"
#include "core/renderable_base.h"
#include "core/renderer.h"

namespace game::core {
struct Color;
struct Vec2;
} // namespace game::core

namespace game::objects {

class Shape : public core::IPhysical, public core::IRenderable, public core::ICollidable {
public:
    Shape() = delete;
    ~Shape() noexcept override = default;

    Shape(const Shape&) noexcept = default;
    Shape& operator=(const Shape&) noexcept = default;

    Shape(Shape&&) noexcept = default;
    Shape& operator=(Shape&&) noexcept = default;

    Shape(core::Vec2 pos, core::Color color) noexcept;

    void integrate(float dt) noexcept override;

    [[nodiscard]] core::Vec2 get_pos() const noexcept override;
    void set_pos(core::Vec2 pos) noexcept override;

    [[nodiscard]] core::Vec2 get_vel() const noexcept override;
    void set_vel(core::Vec2 vel) noexcept override;

    [[nodiscard]] core::Vec2 get_acc() const noexcept override;
    void set_acc(core::Vec2 acc) noexcept override;

    [[nodiscard]] float get_rot_angle() const noexcept override;
    void set_rot_angle(float angle) noexcept override;

    [[nodiscard]] float get_ang_vel() const noexcept override;
    void set_ang_vel(float ang_vel) noexcept override;

    void render(core::IRenderer&) const noexcept override;

    [[nodiscard]] core::Color get_color() const noexcept override;
    void set_color(core::Color color) noexcept override;

    [[nodiscard]] std::vector<core::Vec2> get_vertices_world() const noexcept override;

private:
    core::PhysicalBase m_physical;
    core::RenderableBase m_renderable;
};

} // namespace game::objects

#endif // OBJECTS_SHAPE_H
