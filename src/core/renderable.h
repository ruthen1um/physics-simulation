#ifndef CORE_RENDERABLE_H
#define CORE_RENDERABLE_H

#include "core/color.h"
#include "core/renderer.h"

namespace game::core {

class IRenderable {
public:
    virtual ~IRenderable() = default;

    virtual void render(IRenderer& renderer) const noexcept = 0;

    [[nodiscard]] virtual Color get_color() const noexcept = 0;
    virtual void set_color(Color color) noexcept = 0;
};

} // namespace game::core

#endif // CORE_RENDERABLE_H
