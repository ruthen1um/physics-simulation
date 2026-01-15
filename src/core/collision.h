#ifndef CORE_COLLISION_H
#define CORE_COLLISION_H

#include "core/math.h"
#include "core/window.h"
#include "objects/polygon.h"

#include <algorithm>
#include <array>

namespace game::core {

template <std::size_t N>
using Vertices = std::array<Vec2, N>;

template <std::size_t N>
[[nodiscard]] Vec2 get_uppermost_vertex(const Vertices<N>& verts) {
    const auto comp = [](const Vec2& v1, const Vec2& v2) { return v1.y > v2.y; };
    return *std::max_element(verts.begin(), verts.end(), comp);
}

template <std::size_t N>
[[nodiscard]] Vec2 get_lowermost_vertex(const Vertices<N>& verts) {
    const auto comp = [](const Vec2& v1, const Vec2& v2) { return v1.y > v2.y; };
    return *std::min_element(verts.begin(), verts.end(), comp);
}

template <std::size_t N>
[[nodiscard]] Vec2 get_leftmost_vertex(const Vertices<N>& verts) {
    const auto comp = [](const Vec2& v1, const Vec2& v2) { return v1.x < v2.x; };
    return *std::min_element(verts.begin(), verts.end(), comp);
}

template <std::size_t N>
[[nodiscard]] Vec2 get_rightmost_vertex(const Vertices<N>& verts) {
    const auto comp = [](const Vec2& v1, const Vec2& v2) { return v1.x < v2.x; };
    return *std::max_element(verts.begin(), verts.end(), comp);
}

} // namespace game::core

#endif // CORE_COLLISION_H
