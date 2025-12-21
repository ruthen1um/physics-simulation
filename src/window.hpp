#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <memory>
#include <string>

#include <SDL3/SDL.h>

namespace game {

namespace detail {

class SDLWindowDeleter {
public:
    void operator()(SDL_Window* window) const noexcept {
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
};

class SDLRendererDeleter {
public:
    void operator()(SDL_Renderer* renderer) const noexcept {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
    }
};

} // namespace detail

class SDLWindow {
public:
    int width;
    int height;

    [[nodiscard]] explicit SDLWindow(const std::string& title, int width, int height);
    [[nodiscard]] SDL_Renderer* get_sdl_renderer() noexcept;

private:
    std::unique_ptr<SDL_Window, detail::SDLWindowDeleter> sdl_window;
    std::unique_ptr<SDL_Renderer, detail::SDLRendererDeleter> sdl_renderer;
};

} // namespace game

#endif // WINDOW_HPP
