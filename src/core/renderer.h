#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include "core/color.h"
#include "core/event.h"
#include "core/math.h"

#include <memory>
#include <string>

#include <SDL3/SDL.h>

namespace game::core {

class IRenderer {
public:
    IRenderer() = default;
    virtual ~IRenderer() = default;

    IRenderer(const IRenderer&) = delete;
    IRenderer& operator=(const IRenderer&) = delete;
    IRenderer(IRenderer&&) = delete;
    IRenderer& operator=(IRenderer&&) = delete;

    virtual void render_point(Vec2 v, Color color) noexcept = 0;
    virtual void render_line(Vec2 v1, Vec2 v2, Color color) noexcept = 0;
    virtual void clear(Color color) noexcept = 0;
    virtual void present() noexcept = 0;
};

} // namespace game::core

#endif // CORE_RENDERER_H
