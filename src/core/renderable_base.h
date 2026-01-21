#ifndef CORE_RENDERABLE_BASE_H
#define CORE_RENDERABLE_BASE_H

#include <memory>

#include "core/color.h"
#include "core/renderable.h"

namespace game::core {

class RenderableBase : IRenderable {
public:
    RenderableBase() = delete;
    ~RenderableBase() noexcept override = default;

    RenderableBase(const RenderableBase&) noexcept = default;
    RenderableBase& operator=(const RenderableBase&) noexcept = default;

    RenderableBase(RenderableBase&&) noexcept = default;
    RenderableBase& operator=(RenderableBase&&) noexcept = default;

    explicit RenderableBase(Color color) noexcept;

    void render(IRenderer&) const noexcept override;

    [[nodiscard]] Color get_color() const noexcept override;
    void set_color(Color color) noexcept override;

private:
    Color m_color;
};

} // namespace game::core

#endif // CORE_RENDERABLE_BASE_H
