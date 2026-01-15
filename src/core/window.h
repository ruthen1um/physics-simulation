#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "core/event.h"
#include "core/math.h"

#include <memory>
#include <string>

#include <SDL3/SDL.h>

namespace game::core {

class IWindow {
public:
    IWindow() = default;
    virtual ~IWindow() = default;

    IWindow(const IWindow&) = delete;
    IWindow& operator=(const IWindow&) = delete;
    IWindow(IWindow&&) = delete;
    IWindow& operator=(IWindow&&) = delete;

    virtual void poll_events() noexcept = 0;
    virtual void set_event_handler(EventHandler handler) noexcept = 0;

    [[nodiscard]] virtual bool should_close() const noexcept = 0;

    [[nodiscard]] virtual int get_width() const noexcept = 0;
    [[nodiscard]] virtual int get_height() const noexcept = 0;
};

} // namespace game::core

#endif // CORE_WINDOW_H
