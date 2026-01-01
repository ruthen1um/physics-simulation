#include "window.h"
#include "objects/object.h"

#include <stdexcept>

namespace game {

namespace detail {

void SDLWindowDeleter::operator()(SDL_Window* window) const noexcept {
    if (window) {
        SDL_DestroyWindow(window);
    }
}

void SDLRendererDeleter::operator()(SDL_Renderer* renderer) const noexcept {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
}

} // namespace detail

[[nodiscard]] SDLWindow::SDLWindow(const std::string& title, int width, int height)
    : m_width{width},
      m_height{height},
      m_sdl_window{SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE)},
      m_sdl_renderer{SDL_CreateRenderer(m_sdl_window.get(), nullptr)} {

    if (width <= 0) {
        throw std::invalid_argument{"Window width should be positive"};
    }

    if (height <= 0) {
        throw std::invalid_argument{"Window height should be positive"};
    }

    if (!m_sdl_window) {
        throw std::runtime_error{std::string{"Could not create SDL_Window: "} + SDL_GetError()};
    }

    if (!m_sdl_renderer) {
        throw std::runtime_error{std::string{"Could not create SDL_Renderer: "} + SDL_GetError()};
    }
}

void SDLWindow::render_line(const Vector2D& v1, const Vector2D& v2, const Color& color) noexcept {
    SDL_SetRenderDrawColor(m_sdl_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderLine(m_sdl_renderer.get(), v1.x, v1.y, v2.x, v2.y);
}

void SDLWindow::clear(const Color& color) noexcept {
    SDL_SetRenderDrawColor(m_sdl_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_sdl_renderer.get());
}

void render_object(
    SDLWindow& window, const objects::Object2D& obj, [[maybe_unused]] bool fill
) noexcept {
    auto vertices = obj.get_vertices_global();
    auto begin = vertices.begin();
    auto end = vertices.end();
    for (auto it = begin; it != end && std::next(it) != end; ++it) {
        auto v1 = *it;
        auto v2 = *std::next(it);
        window.render_line(v1, v2, obj.color());
    }
    window.render_line(*std::prev(end), *begin, obj.color());
}

void SDLWindow::present() noexcept {
    SDL_RenderPresent(m_sdl_renderer.get());
}

} // namespace game
