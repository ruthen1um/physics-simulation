#ifndef CORE_COLLIDABLE_H
#define CORE_COLLIDABLE_H

#include "core/vector.h"

#include <vector>

namespace game::core {

class ICollidable {
public:
    virtual ~ICollidable() = default;

    [[nodiscard]] virtual std::vector<Vec2> get_vertices_world() const noexcept = 0;
};

} // namespace game::core

#endif // CORE_COLLIDABLE_H
