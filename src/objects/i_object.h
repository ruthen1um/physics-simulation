#ifndef OBJECTS_I_OBJECT_H
#define OBJECTS_I_OBJECT_H

#include "../core/vec.h"

#include <vector>

namespace game::objects {

class IObject2 {
public:
    IObject2() = default;
    virtual ~IObject2() = default;

    IObject2(const IObject2&) = delete;
    IObject2& operator=(const IObject2&) = delete;
    IObject2(IObject2&&) = delete;
    IObject2& operator=(IObject2&&) = delete;

    virtual void update(float dt) noexcept = 0;

    [[nodiscard]] virtual std::vector<core::Vec2> get_vertices_global() const noexcept = 0;
    [[nodiscard]] virtual std::vector<core::Vec2> get_vertices_local() const noexcept = 0;

    [[nodiscard]] virtual core::Vec2 top() const noexcept = 0;
    [[nodiscard]] virtual core::Vec2 right() const noexcept = 0;
    [[nodiscard]] virtual core::Vec2 bottom() const noexcept = 0;
    [[nodiscard]] virtual core::Vec2 left() const noexcept = 0;
};

} // namespace game::objects

#endif // OBJECTS_I_OBJECT_H
