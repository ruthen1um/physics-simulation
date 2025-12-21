#include "rectangle.hpp"

#include "../object.hpp"
#include "../vector.hpp"
#include "../exceptions.hpp"

#include <SDL3/SDL.h>

namespace game::objects {

Rectangle::Rectangle(float x, float y, float w, float h)
    : Object2D{Vector2D{x, y}}, w{w}, h{h} {
    if (w < 0 || h < 0) {
        throw exceptions::ArgumentException{"w and h should be non-negative"};
    }
}

void Rectangle::render(SDL_Renderer* renderer) const noexcept {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    auto rect = SDL_FRect{left_x(), top_y(), h, w};
    SDL_RenderFillRect(renderer, &rect);
}

[[nodiscard]] float Rectangle::top_y() const noexcept {
    return pos.y - h / 2.0f;
}

[[nodiscard]] float Rectangle::bottom_y() const noexcept {
    return pos.y + h / 2.0f;
}

[[nodiscard]] float Rectangle::left_x() const noexcept {
    return pos.x - w / 2.0f;
}

[[nodiscard]] float Rectangle::right_x() const noexcept {
    return pos.x + w / 2.0f;
}

} // namespace game::objects
