#include "backends/sdl/renderer.h"
#include "backends/sdl/window.h"
#include "core/color.h"
#include "core/math.h"

#include <stdexcept>
#include <string>

#include <SDL3/SDL_error.h>

namespace game::backends::sdl {

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

void SDLRenderer::render_point(core::Vec2 v, core::Color color) noexcept {
    SDL_SetRenderDrawColor(m_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderPoint(m_renderer.get(), v.x, v.y);
}

void SDLRenderer::render_line(core::Vec2 v1, core::Vec2 v2, core::Color color) noexcept {
    SDL_SetRenderDrawColor(m_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_renderer.get(), v1.x, v1.y, v2.x, v2.y);
}

void SDLRenderer::clear(core::Color color) noexcept {
    SDL_SetRenderDrawColor(m_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer.get());
}

void SDLRenderer::present() noexcept {
    SDL_RenderPresent(m_renderer.get());
}

[[nodiscard]] SDL_Renderer* SDLRenderer::get_raw() {
    return m_renderer.get();
}

} // namespace game::backends::sdl
