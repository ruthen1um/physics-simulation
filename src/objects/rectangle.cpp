#include "rectangle.hpp"

#include "../object.hpp"
#include "../vector.hpp"
#include "../exceptions.hpp"

#include <SDL3/SDL.h>

namespace game::objects {

Rectangle::Rectangle(const float x, const float y, const float w, const float h, const float mass)
    : Object2D{Vector2D{x, y}, mass}, w{w}, h{h} {
    if (w < 0 || h < 0) {
        throw exceptions::ArgumentException{"w and h should be non-negative"};
    }
}

void Rectangle::render(SDL_Renderer* renderer) const noexcept {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    auto rect = SDL_FRect{left(), top(), h, w};
    SDL_RenderFillRect(renderer, &rect);
}

[[nodiscard]] float Rectangle::top() const noexcept {
    return pos.y - h / 2.0f;
}

[[nodiscard]] float Rectangle::bottom() const noexcept {
    return pos.y + h / 2.0f;
}

[[nodiscard]] float Rectangle::left() const noexcept {
    return pos.x - w / 2.0f;
}

[[nodiscard]] float Rectangle::right() const noexcept {
    return pos.x + w / 2.0f;
}

} // namespace game::objects
