#include "sdl_window.h"
#include "../core/event.h"
#include "../core/input.h"

#include <functional>
#include <stdexcept>
#include <variant>

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>

using game::core::EventHandler;
using game::core::EventType;
using game::core::Key;
using game::core::KeyEventData;
using game::core::KeyState;
using game::core::MouseButton;
using game::core::MouseButtonEventData;
using game::core::MouseButtonState;
using game::core::MouseMotionEventData;
using game::core::MousePos;

namespace game::graphics {

namespace detail {

void SDLWindowDeleter::operator()(SDL_Window* window) const noexcept {
    if (window) {
        SDL_DestroyWindow(window);
    }
}

Key map_sdl_scancode(SDL_Scancode scancode) {
    switch (scancode) {
        case SDL_SCANCODE_ESCAPE:
            return Key::Escape;
        case SDL_SCANCODE_BACKSPACE:
            return Key::Backspace;
        default:
            return Key::Unknown;
    }
}

MouseButton map_sdl_mouse_button(Uint8 button) {
    switch (button) {
        case SDL_BUTTON_LEFT:
            return MouseButton::Left;
        case SDL_BUTTON_MIDDLE:
            return MouseButton::Middle;
        case SDL_BUTTON_RIGHT:
            return MouseButton::Right;
        default:
            return MouseButton::Unknown;
    }
}

} // namespace detail

[[nodiscard]] SDLWindow::SDLWindow(const std::string& title, int width, int height)
    : m_width{width},
      m_height{height},
      m_window{SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE)} {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error{std::string{"Could not init SDL: "} + SDL_GetError()};
    }

    if (width <= 0) {
        throw std::invalid_argument{"Window width should be positive"};
    }

    if (height <= 0) {
        throw std::invalid_argument{"Window height should be positive"};
    }

    if (!m_window) {
        throw std::runtime_error{std::string{"Could not create SDL_Window: "} + SDL_GetError()};
    }
}

SDLWindow::~SDLWindow() {
    SDL_Quit();
}

void SDLWindow::poll_events() noexcept {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_EVENT_QUIT) {
            m_should_close = true;
        } else if (ev.type == SDL_EVENT_WINDOW_RESIZED) {
            m_width = ev.window.data1;
            m_height = ev.window.data2;
        } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_UP || ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            const auto button = detail::map_sdl_mouse_button(ev.button.button);
            const auto state = ev.type == SDL_EVENT_MOUSE_BUTTON_UP ? MouseButtonState::Up
                                                                    : MouseButtonState::Down;
            const auto pos = MousePos{static_cast<int>(ev.button.x), static_cast<int>(ev.button.y)};
            m_handlers[EventType::MouseButtonEvent](MouseButtonEventData{button, state, pos});
        } else if (ev.type == SDL_EVENT_MOUSE_MOTION) {
            const auto pos = MousePos{static_cast<int>(ev.button.x), static_cast<int>(ev.button.y)};
            m_handlers[EventType::MouseMotionEvent](MouseMotionEventData{pos});
        } else if (ev.type == SDL_EVENT_KEY_DOWN || ev.type == SDL_EVENT_KEY_UP) {
            const auto key = detail::map_sdl_scancode(ev.key.scancode);
            const auto state = ev.type == SDL_EVENT_MOUSE_BUTTON_UP ? KeyState::Up : KeyState::Down;
            m_handlers[EventType::KeyEvent](KeyEventData{key, state});
        }
    }
}

void SDLWindow::set_event_handler(EventType type, EventHandler handler) noexcept {
    m_handlers.insert_or_assign(type, handler);
}

[[nodiscard]] bool SDLWindow::should_close() const noexcept {
    return m_should_close;
}

[[nodiscard]] int SDLWindow::width() const noexcept {
    return m_width;
}

[[nodiscard]] int SDLWindow::height() const noexcept {
    return m_height;
}

[[nodiscard]] SDL_Window* SDLWindow::get_raw() noexcept {
    return m_window.get();
}

} // namespace game::graphics
