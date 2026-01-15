#ifndef OBJECTS_POLYGON_H
#define OBJECTS_POLYGON_H

#include "core/collision.h"
#include "core/color.h"
#include "core/interfaces.h"
#include "core/math.h"
#include "core/physical_base.h"
#include "core/renderer.h"

#include <array>
#include <cstddef>
#include <exception>
#include <memory>
#include <stdexcept>

namespace game::objects {

enum class PolygonType { Rectangle, Triangle };

template <std::size_t N>
class Polygon : public core::IPhysical, public core::IRenderable {
public:
    Polygon() = delete;

    ~Polygon() noexcept = default;

    constexpr Polygon(const Polygon&) noexcept = default;
    constexpr Polygon& operator=(const Polygon&) noexcept = default;

    constexpr Polygon(Polygon&&) noexcept = default;
    constexpr Polygon& operator=(Polygon&&) noexcept = default;

    /**
     * @param x Center x coordinate of the rectangle.
     * @param y Center y coordinate of the rectangle.
     * @param w Width of the rectangle.
     * @param h Height of the rectangle.
     * @param c Color of the rectangle.
     */
    static Polygon rectangle(float x, float y, float w, float h, core::Color c) {
        static_assert(N == 4, "Rectangle must always have 4 vertices");

        if (w < 0) {
            throw std::invalid_argument{"Rectangle width must be non-negative"};
        }

        if (h < 0) {
            throw std::invalid_argument{"Rectangle height must be non-negative"};
        }

        using core::Vec2;

        auto vertices = core::Vertices<4>{
            Vec2{-w / 2, -h / 2},
            Vec2{+w / 2, -h / 2},
            Vec2{+w / 2, +h / 2},
            Vec2{-w / 2, +h / 2},
        };

        return Polygon{std::move(vertices), {x, y}, c};
    }

    constexpr PolygonType get_type() const noexcept {
        switch (m_vertices.size()) {
            case 3:
                return PolygonType::Triangle;
            case 4:
                return PolygonType::Rectangle;
            default:
                // unreachable
                std::terminate();
        }
    };

    void integrate(float dt) noexcept override {
        m_physical.integrate(dt);
    }

    [[nodiscard]] core::Vec2 get_pos() const noexcept override {
        return m_physical.get_pos();
    }

    void set_pos(core::Vec2 pos) noexcept override {
        m_physical.set_pos(std::move(pos));
    }

    [[nodiscard]] core::Vec2 get_vel() const noexcept override {
        return m_physical.get_vel();
    }

    void set_vel(core::Vec2 vel) noexcept override {
        m_physical.set_vel(std::move(vel));
    }

    [[nodiscard]] core::Vec2 get_acc() const noexcept override {
        return m_physical.get_acc();
    }

    void set_acc(core::Vec2 acc) noexcept override {
        m_physical.set_acc(std::move(acc));
    }

    [[nodiscard]] float get_rot_angle() const noexcept override {
        return m_physical.get_rot_angle();
    }

    void set_rot_angle(float angle) noexcept override {
        m_physical.set_rot_angle(std::move(angle));
    }

    [[nodiscard]] float get_ang_vel() const noexcept override {
        return m_physical.get_ang_vel();
    }

    void set_ang_vel(float ang_vel) noexcept override {
        m_physical.set_ang_vel(std::move(ang_vel));
    }

    void render(core::IRenderer& renderer) const noexcept override {
        const auto vertices = get_vertices_world();
        const auto n = vertices.size();
        for (auto i = std::size_t{0}; i < n; ++i) {
            renderer.render_line(vertices[i], vertices[(i + 1) % n], get_color());
        }
    }

    [[nodiscard]] core::Color get_color() const noexcept override {
        return m_color;
    }

    void set_color(core::Color color) noexcept override {
        m_color = std::move(color);
    }

    constexpr auto get_vertices_world() const noexcept {
        auto vertices_world = core::Vertices<N>{m_vertices};
        for (auto& v : vertices_world) {
            v = get_pos() + rotate(v, get_rot_angle());
        }
        return vertices_world;
    }

private:
    constexpr Polygon(core::Vertices<N>&& verts, core::Vec2 pos, core::Color color) noexcept
        : m_vertices{std::move(verts)}, m_physical{pos}, m_color{color} {
        static_assert(N == 3 || N == 4, "A polygon must only be a rectangle or a triangle");
    };

    core::Vertices<N> m_vertices;
    core::PhysicalBase m_physical;
    core::Color m_color;
};

using Tri = Polygon<3>;
using Quad = Polygon<4>;

} // namespace game::objects

#endif // OBJECTS_POLYGON_H
