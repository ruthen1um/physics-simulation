#include "core/renderable_base.h"

#include <utility>

namespace game::core {

RenderableBase::RenderableBase(Color color) noexcept
    : m_color{std::move(color)} {}

void RenderableBase::render(IRenderer&) const noexcept {}

[[nodiscard]] Color RenderableBase::get_color() const noexcept {
    return m_color;
}

void RenderableBase::set_color(Color color) noexcept {
    m_color = std::move(color);
}

} // namespace game::core
