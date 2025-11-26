#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "../object.hpp"

namespace game::objects {

class Rectangle: public Object2D {
private:
    const float w;
    const float h;
public:
    Rectangle(const float x, const float y, const float w, const float h, const float mass);

    virtual void render(SDL_Renderer* renderer) const noexcept override;

    [[nodiscard]] virtual float top() const noexcept override;
    [[nodiscard]] virtual float bottom() const noexcept override;
    [[nodiscard]] virtual float left() const noexcept override;
    [[nodiscard]] virtual float right() const noexcept override;
};

} // namespace game::objects

#endif // RECTANGLE_HPP
