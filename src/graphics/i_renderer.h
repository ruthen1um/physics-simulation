#ifndef GRAPHICS_I_RENDERER_H
#define GRAPHICS_I_RENDERER_H

#include "../core/event.h"
#include "../core/vec.h"
#include "../objects/object.h"

#include <memory>
#include <string>

#include <SDL3/SDL.h>

namespace game::graphics {

class IRenderer {
public:
    IRenderer() = default;
    virtual ~IRenderer() = default;

    IRenderer(const IRenderer&) = delete;
    IRenderer& operator=(const IRenderer&) = delete;
    IRenderer(IRenderer&&) = delete;
    IRenderer& operator=(IRenderer&&) = delete;

    virtual void render_point(const core::Vec2& v, const core::Color& color) noexcept = 0;
    virtual void
    render_line(const core::Vec2& v1, const core::Vec2& v2, const core::Color& color) noexcept = 0;
    virtual void clear(const core::Color& color) noexcept = 0;
    virtual void present() noexcept = 0;
};

} // namespace game::graphics

#endif // GRAPHICS_I_RENDERER_H
