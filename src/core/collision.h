#ifndef CORE_COLLISION_H
#define CORE_COLLISION_H

#include <vector>

#include "core/vector.h"
#include "core/window.h"

namespace game::core {

[[nodiscard]] Vec2 get_uppermost_vertex(const std::vector<Vec2>& verts);
[[nodiscard]] Vec2 get_lowermost_vertex(const std::vector<Vec2>& verts);
[[nodiscard]] Vec2 get_leftmost_vertex(const std::vector<Vec2>& verts);
[[nodiscard]] Vec2 get_rightmost_vertex(const std::vector<Vec2>& verts);

} // namespace game::core

#endif // CORE_COLLISION_H
