#ifndef BACKENDS_SDL_RENDERER_H
#define BACKENDS_SDL_RENDERER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <memory>
#include <string>

#include "core/color.h"
#include "core/math.h"
#include "core/renderer.h"
#include "window.h"

namespace game::backends::sdl {
class SDLWindow;
} // namespace game::backends::sdl

namespace game::backends::sdl {

namespace detail {

class SDLRendererDeleter {
public:
    void operator()(SDL_Renderer* renderer) const noexcept;
};

} // namespace detail

class SDLRenderer : public core::IRenderer {
public:
    explicit SDLRenderer(SDLWindow& window);

    void render_point(core::Vec2 v, core::Color color) noexcept override;
    void render_line(core::Vec2 v1, core::Vec2 v2, core::Color color) noexcept override;
    void clear(core::Color color) noexcept override;
    void present() noexcept override;

    [[nodiscard]] SDL_Renderer* get_raw();

private:
    std::unique_ptr<SDL_Renderer, detail::SDLRendererDeleter> m_renderer;
};

} // namespace game::backends::sdl

#endif // BACKENDS_SDL_RENDERER_H
