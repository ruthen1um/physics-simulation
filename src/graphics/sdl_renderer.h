#ifndef GRAPHICS_SDL_RENDERER_H
#define GRAPHICS_SDL_RENDERER_H

#include "../core/color.h"
#include "../core/vec.h"
#include "../objects/object.h"
#include "i_renderer.h"
#include "sdl_window.h"

#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

namespace game::graphics {

namespace detail {

class SDLRendererDeleter {
public:
    void operator()(SDL_Renderer* renderer) const noexcept;
};

} // namespace detail

class SDLRenderer : public IRenderer {
public:
    explicit SDLRenderer(SDLWindow& window);

    void render_point(const core::Vec2& v, const core::Color& color) noexcept override;
    void render_line(
        const core::Vec2& v1, const core::Vec2& v2, const core::Color& color
    ) noexcept override;
    void clear(const core::Color& color) noexcept override;
    void present() noexcept override;

    [[nodiscard]] SDL_Renderer* get_raw();

private:
    std::unique_ptr<SDL_Renderer, detail::SDLRendererDeleter> m_renderer;
};

} // namespace game::graphics

#endif // GRAPHICS_SDL_RENDERER_H
