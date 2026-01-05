#ifndef OBJECTS_RECTANGLE_H
#define OBJECTS_RECTANGLE_H

#include "../core/vec.h"
#include "object.h"

#include <vector>

namespace game::objects {

class Rectangle : public Object2 {
public:
    Rectangle(float center_x, float center_y, float w, float h);

    [[nodiscard]] std::vector<core::Vec2> get_vertices_global() const noexcept override;
    [[nodiscard]] std::vector<core::Vec2> get_vertices_local() const noexcept override;

    [[nodiscard]] core::Vec2 top() const noexcept override;
    [[nodiscard]] core::Vec2 right() const noexcept override;
    [[nodiscard]] core::Vec2 bottom() const noexcept override;
    [[nodiscard]] core::Vec2 left() const noexcept override;

private:
    float m_w;
    float m_h;
    std::vector<core::Vec2> m_vertices_local;
};

} // namespace game::objects

#endif // OBJECTS_RECTANGLE_H
