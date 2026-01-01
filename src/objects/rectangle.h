#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../vector.h"
#include "object.h"

#include <vector>

namespace game::objects {

class Rectangle : public Object2D {
public:
    Rectangle(float center_x, float center_y, float w, float h);

    [[nodiscard]] std::vector<Vector2D> get_vertices_global() const noexcept override;
    [[nodiscard]] std::vector<Vector2D> get_vertices_local() const noexcept override;

    [[nodiscard]] Vector2D top() const noexcept override;
    [[nodiscard]] Vector2D right() const noexcept override;
    [[nodiscard]] Vector2D bottom() const noexcept override;
    [[nodiscard]] Vector2D left() const noexcept override;

private:
    float m_w;
    float m_h;
    std::vector<Vector2D> m_vertices_local;
};

} // namespace game::objects

#endif // RECTANGLE_H
