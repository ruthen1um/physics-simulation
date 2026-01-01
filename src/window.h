#ifndef WINDOW_H
#define WINDOW_H

#include "color.h"
#include "objects/object.h"
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
    int m_width;
    int m_height;

    [[nodiscard]] explicit SDLWindow(const std::string& title, int width, int height);

    void render_line(const Vector2D& v1, const Vector2D& v2, const Color& color) noexcept;
    void clear(const Color& color) noexcept;
    void present() noexcept;

private:
    std::unique_ptr<SDL_Window, detail::SDLWindowDeleter> m_sdl_window;
    std::unique_ptr<SDL_Renderer, detail::SDLRendererDeleter> m_sdl_renderer;
};

void render_object(
    SDLWindow& window, const objects::Object2D& obj, [[maybe_unused]] bool fill = true
) noexcept;

} // namespace game

#endif // WINDOW_H
