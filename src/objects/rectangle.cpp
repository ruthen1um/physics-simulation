#include "rectangle.h"

#include "../constants.h"
#include "../vector.h"
#include "object.h"

#include <algorithm>
#include <array>
#include <stdexcept>

#include <SDL3/SDL.h>
#include <gcem.hpp>

namespace game::objects {

Rectangle::Rectangle(float center_x, float center_y, float w, float h)
    : Object2D{{center_x, center_y}}, m_w{w}, m_h{h} {
    if (w < 0) {
        throw std::invalid_argument{"Rectangle constructor: w must be non-negative"};
    }

    if (h < 0) {
        throw std::invalid_argument{"Rectangle constructor: h must be non-negative"};
    }

    m_vertices_local.emplace_back(-m_w / 2, -m_h / 2);
    m_vertices_local.emplace_back(+m_w / 2, -m_h / 2);
    m_vertices_local.emplace_back(+m_w / 2, +m_h / 2);
    m_vertices_local.emplace_back(-m_w / 2, +m_h / 2);
}

[[nodiscard]] std::vector<Vector2D> Rectangle::get_vertices_global() const noexcept {
    return {
        m_pos + m_vertices_local[0].rotate(m_angle),
        m_pos + m_vertices_local[1].rotate(m_angle),
        m_pos + m_vertices_local[2].rotate(m_angle),
        m_pos + m_vertices_local[3].rotate(m_angle),
    };
}

[[nodiscard]] std::vector<Vector2D> Rectangle::get_vertices_local() const noexcept {
    return m_vertices_local;
}

[[nodiscard]] Vector2D Rectangle::top() const noexcept {
    const auto vertices_global = get_vertices_global();
    return *std::min_element(
        vertices_global.begin(), vertices_global.end(),
        [](const Vector2D& v1, const Vector2D& v2) { return v1.y < v2.y; }
    );
}

[[nodiscard]] Vector2D Rectangle::right() const noexcept {
    const auto vertices_global = get_vertices_global();
    return *std::max_element(
        vertices_global.begin(), vertices_global.end(),
        [](const Vector2D& v1, const Vector2D& v2) { return v1.x < v2.x; }
    );
}

[[nodiscard]] Vector2D Rectangle::bottom() const noexcept {
    const auto vertices_global = get_vertices_global();
    return *std::max_element(
        vertices_global.begin(), vertices_global.end(),
        [](const Vector2D& v1, const Vector2D& v2) { return v1.y < v2.y; }
    );
}

[[nodiscard]] Vector2D Rectangle::left() const noexcept {
    const auto vertices_global = get_vertices_global();
    return *std::min_element(
        vertices_global.begin(), vertices_global.end(),
        [](const Vector2D& v1, const Vector2D& v2) { return v1.x < v2.x; }
    );
}

} // namespace game::objects
