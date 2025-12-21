#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "../object.hpp"

namespace game::objects {

class Rectangle: public Object2D {
private:
    float w;
    float h;
public:
    Rectangle(float x, float y, float w, float h);

    virtual void render(SDL_Renderer* renderer) const noexcept override;

    [[nodiscard]] virtual float top_y() const noexcept override;
    [[nodiscard]] virtual float bottom_y() const noexcept override;
    [[nodiscard]] virtual float left_x() const noexcept override;
    [[nodiscard]] virtual float right_x() const noexcept override;
};

} // namespace game::objects

#endif // RECTANGLE_HPP
