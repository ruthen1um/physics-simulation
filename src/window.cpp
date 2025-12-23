#include "window.h"
#include "object.h"

#include "exceptions.h"

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
    : width{width},
      height{height},
      sdl_window{SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE)},
      sdl_renderer{SDL_CreateRenderer(sdl_window.get(), nullptr)} {

    if (width <= 0) {
        throw exceptions::SystemException{"Window width should be positive"};
    }

    if (height <= 0) {
        throw exceptions::SystemException{"Window height should be positive"};
    }

    if (!sdl_window) {
        throw exceptions::SystemException{
            std::string{"Could not create SDL_Window: "} + SDL_GetError()
        };
    }

    if (!sdl_renderer) {
        throw exceptions::SystemException{
            std::string{"Could not create SDL_Renderer: "} + SDL_GetError()
        };
    }
}

void SDLWindow::render_line(const Vector2D& v1, const Vector2D& v2, const Color& color) noexcept {
    SDL_SetRenderDrawColor(sdl_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderLine(sdl_renderer.get(), v1.x, v1.y, v2.x, v2.y);
}

void SDLWindow::render_bg(const Color& color) noexcept {
    SDL_SetRenderDrawColor(sdl_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderClear(sdl_renderer.get());
}

void SDLWindow::render(const Object2D& obj, [[maybe_unused]] bool fill) noexcept {
    auto vertices = obj.get_vertices_global();
    auto begin = vertices.begin();
    auto end = vertices.end();
    for (auto it = begin; it != end && std::next(it) != end; ++it) {
        auto v1 = *it;
        auto v2 = *std::next(it);
        render_line(v1, v2, obj.color);
    }
    render_line(*std::prev(end), *begin, obj.color);
}

void SDLWindow::present() noexcept { SDL_RenderPresent(sdl_renderer.get()); }

} // namespace game
