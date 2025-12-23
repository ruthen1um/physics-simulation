#ifndef WINDOW_H
#define WINDOW_H

#include "color.h"
#include "object.h"
#include "vector.h"

#include <memory>
#include <string>

#include <SDL3/SDL.h>

namespace game {

namespace detail {

class SDLWindowDeleter {
public:
    void operator()(SDL_Window* window) const noexcept;
};

class SDLRendererDeleter {
public:
    void operator()(SDL_Renderer* window) const noexcept;
};

} // namespace detail

class SDLWindow {
public:
    int width;
    int height;

    [[nodiscard]] explicit SDLWindow(const std::string& title, int width, int height);

    void render_line(const Vector2D& v1, const Vector2D& v2, const Color& color) noexcept;
    void render_bg(const Color& color) noexcept;
    void render(const Object2D& obj, [[maybe_unused]] bool fill = true) noexcept;
    void present() noexcept;

private:
    std::unique_ptr<SDL_Window, detail::SDLWindowDeleter> sdl_window;
    std::unique_ptr<SDL_Renderer, detail::SDLRendererDeleter> sdl_renderer;
};

} // namespace game

#endif // WINDOW_H
