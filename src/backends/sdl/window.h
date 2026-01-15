#ifndef BACKENDS_SDL_WINDOW_H
#define BACKENDS_SDL_WINDOW_H

#include "core/event.h"
#include "core/window.h"

#include <memory>
#include <string>

#include <SDL3/SDL_video.h>

namespace game::backends::sdl {

namespace detail {

class SDLWindowDeleter {
public:
    void operator()(SDL_Window* window) const noexcept;
};

} // namespace detail

class SDLWindow : public core::IWindow {
public:
    explicit SDLWindow(const std::string& title, int width, int height);
    ~SDLWindow() override;

    SDLWindow(const SDLWindow&) = delete;
    SDLWindow& operator=(const SDLWindow&) = delete;
    SDLWindow(SDLWindow&&) = delete;
    SDLWindow& operator=(SDLWindow&&) = delete;

    void poll_events() noexcept override;
    void set_event_handler(core::EventHandler handler) noexcept override;

    [[nodiscard]] bool should_close() const noexcept override;

    [[nodiscard]] int get_width() const noexcept override;
    [[nodiscard]] int get_height() const noexcept override;

    [[nodiscard]] SDL_Window* get_raw() noexcept;

private:
    bool m_should_close{false};
    int m_width;
    int m_height;
    std::unique_ptr<SDL_Window, detail::SDLWindowDeleter> m_window;
    core::EventHandler m_handler;
};

} // namespace game::backends::sdl

#endif // BACKENDS_SDL_WINDOW_H
