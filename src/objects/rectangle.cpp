#include "rectangle.h"

#include "../constants.h"
#include "../exceptions.h"
#include "../object.h"
#include "../vector.h"

#include <algorithm>
#include <array>

#include <SDL3/SDL.h>
#include <gcem.hpp>

namespace game::objects {

Rectangle::Rectangle(float center_x, float center_y, float w, float h)
    : Object2D{{center_x, center_y}}, w{w}, h{h} {
    if (w < 0 || h < 0) {
        throw exceptions::ArgumentException{"w and h should be non-negative"};
    }
}

void Rectangle::update(float dt) noexcept {
    constexpr auto tau = 2 * constants::PI;
    Object2D::update(dt);
    if (rotating) {
        angle += tau * dt;
        if (angle >= tau) {
            angle -= tau;
        }
    }
}

[[nodiscard]] std::vector<Vector2D> Rectangle::get_vertices_global() const noexcept {
    const auto vertices_local = get_vertices_local();
    return {
        pos + vertices_local[0].rotate(angle),
        pos + vertices_local[1].rotate(angle),
        pos + vertices_local[2].rotate(angle),
        pos + vertices_local[3].rotate(angle),
    };
}

[[nodiscard]] std::vector<Vector2D> Rectangle::get_vertices_local() const noexcept {
    return {
        {-w / 2, -h / 2},
        {+w / 2, -h / 2},
        {+w / 2, +h / 2},
        {-w / 2, +h / 2},
    };
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
