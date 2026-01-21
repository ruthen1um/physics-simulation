#include <vector>

#include "core/vector.h"
#include "objects/shape.h"

namespace game::core {
struct Color;
} // namespace game::core

namespace game::objects {

class Rectangle : public Shape {
public:
    Rectangle() = delete;
    ~Rectangle() noexcept override = default;

    Rectangle(const Rectangle&) noexcept = default;
    Rectangle& operator=(const Rectangle&) noexcept = default;

    Rectangle(Rectangle&&) noexcept = default;
    Rectangle& operator=(Rectangle&&) noexcept = default;

    Rectangle(float x, float y, float w, float h, core::Color c);

    void render(core::IRenderer& renderer) const noexcept override;

    [[nodiscard]] std::vector<core::Vec2> get_vertices_world() const noexcept override;

private:
    std::vector<core::Vec2> m_vertices;
};

} // namespace game::objects
