#include "objects/rectangle.h"

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "core/color.h"
#include "core/renderer.h"

namespace game::objects {

Rectangle::Rectangle(float x, float y, float w, float h, core::Color c)
    : Shape{{x, y}, std::move(c)},
      m_vertices{
          core::Vec2{-w / 2, -h / 2},
          core::Vec2{+w / 2, -h / 2},
          core::Vec2{+w / 2, +h / 2},
          core::Vec2{-w / 2, +h / 2},
      } {
    if (w < 0) {
        throw std::invalid_argument{"Rectangle width must be non-negative"};
    }

    if (h < 0) {
        throw std::invalid_argument{"Rectangle height must be non-negative"};
    }
}

void Rectangle::render(core::IRenderer& renderer) const noexcept {
    const auto vertices = get_vertices_world();
    const auto n = vertices.size();
    for (auto i = std::size_t{0}; i < n; ++i) {
        renderer.render_line(vertices[i], vertices[(i + 1) % n], get_color());
    }
}

[[nodiscard]] std::vector<core::Vec2> Rectangle::get_vertices_world() const noexcept {
    auto vertices_world = m_vertices;
    for (auto& v : vertices_world) {
        v = get_pos() + rotate(v, get_rot_angle());
    }
    return vertices_world;
}

} // namespace game::objects
