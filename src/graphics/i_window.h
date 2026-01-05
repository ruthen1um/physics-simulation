#ifndef GRAPHICS_I_WINDOW_H
#define GRAPHICS_I_WINDOW_H

#include "../core/event.h"
#include "../core/vec.h"
#include "../objects/object.h"

#include <memory>
#include <string>

#include <SDL3/SDL.h>

namespace game::graphics {

class IWindow {
public:
    IWindow() = default;
    virtual ~IWindow() = default;

    IWindow(const IWindow&) = delete;
    IWindow& operator=(const IWindow&) = delete;
    IWindow(IWindow&&) = delete;
    IWindow& operator=(IWindow&&) = delete;

    virtual void poll_events() noexcept = 0;
    virtual void set_event_handler(core::EventType type, core::EventHandler handler) noexcept = 0;

    [[nodiscard]] virtual bool should_close() const noexcept = 0;

    [[nodiscard]] virtual int width() const noexcept = 0;
    [[nodiscard]] virtual int height() const noexcept = 0;
};

} // namespace game::graphics

#endif // GRAPHICS_I_WINDOW_H
