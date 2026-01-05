#ifndef GRAPHICS_SDL_WINDOW_H
#define GRAPHICS_SDL_WINDOW_H

#include "../core/event.h"
#include "i_window.h"

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL3/SDL_video.h>

namespace game::graphics {

namespace detail {

class SDLWindowDeleter {
public:
    void operator()(SDL_Window* window) const noexcept;
};

} // namespace detail

class SDLWindow : public IWindow {
public:
    explicit SDLWindow(const std::string& title, int width, int height);
    ~SDLWindow() override;

    SDLWindow(const SDLWindow&) = delete;
    SDLWindow& operator=(const SDLWindow&) = delete;
    SDLWindow(SDLWindow&&) = delete;
    SDLWindow& operator=(SDLWindow&&) = delete;

    void poll_events() noexcept override;
    void set_event_handler(core::EventType type, core::EventHandler handler) noexcept override;

    [[nodiscard]] bool should_close() const noexcept override;

    [[nodiscard]] int width() const noexcept override;
    [[nodiscard]] int height() const noexcept override;

    [[nodiscard]] SDL_Window* get_raw() noexcept;

private:
    bool m_should_close{false};
    int m_width;
    int m_height;
    std::unique_ptr<SDL_Window, detail::SDLWindowDeleter> m_window;
    std::unordered_map<core::EventType, core::EventHandler> m_handlers;
};

} // namespace game::graphics

#endif // GRAPHICS_SDL_WINDOW_H
