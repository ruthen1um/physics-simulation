#include "core/collision.h"

#include <algorithm>

namespace game::core {

[[nodiscard]] Vec2 get_uppermost_vertex(const std::vector<Vec2>& verts) {
    const auto comp = [](const Vec2& v1, const Vec2& v2) { return v1.y > v2.y; };
    return *std::max_element(verts.begin(), verts.end(), comp);
}

[[nodiscard]] Vec2 get_lowermost_vertex(const std::vector<Vec2>& verts) {
    const auto comp = [](const Vec2& v1, const Vec2& v2) { return v1.y > v2.y; };
    return *std::min_element(verts.begin(), verts.end(), comp);
}

[[nodiscard]] Vec2 get_leftmost_vertex(const std::vector<Vec2>& verts) {
    const auto comp = [](const Vec2& v1, const Vec2& v2) { return v1.x < v2.x; };
    return *std::min_element(verts.begin(), verts.end(), comp);
}

[[nodiscard]] Vec2 get_rightmost_vertex(const std::vector<Vec2>& verts) {
    const auto comp = [](const Vec2& v1, const Vec2& v2) { return v1.x < v2.x; };
    return *std::max_element(verts.begin(), verts.end(), comp);
}

} // namespace game::core
