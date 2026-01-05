#include "sdl_renderer.h"
#include "../core/color.h"
#include "../core/vec.h"
#include "../objects/object.h"

#include <stdexcept>

using game::core::Color;
using game::core::Vec2;

namespace game::graphics {

namespace detail {

void SDLRendererDeleter::operator()(SDL_Renderer* renderer) const noexcept {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
}

} // namespace detail

SDLRenderer::SDLRenderer(SDLWindow& window)
    : m_renderer{SDL_CreateRenderer(window.get_raw(), nullptr)} {

    if (!m_renderer) {
        throw std::runtime_error{std::string{"Could not create SDL_Renderer: "} + SDL_GetError()};
    }
}

void SDLRenderer::render_point(const Vec2& v, const Color& color) noexcept {
    SDL_SetRenderDrawColor(m_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_renderer.get(), v.x, v.y);
}

void SDLRenderer::render_line(const Vec2& v1, const Vec2& v2, const Color& color) noexcept {
    SDL_SetRenderDrawColor(m_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_renderer.get(), v1.x, v1.y, v2.x, v2.y);
}

void SDLRenderer::clear(const Color& color) noexcept {
    SDL_SetRenderDrawColor(m_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer.get());
}

void SDLRenderer::present() noexcept {
    SDL_RenderPresent(m_renderer.get());
}

[[nodiscard]] SDL_Renderer* SDLRenderer::get_raw() {
    return m_renderer.get();
}

} // namespace game::graphics
