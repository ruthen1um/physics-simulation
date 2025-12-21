#include "window.hpp"
#include "exceptions.hpp"

namespace game {

[[nodiscard]] SDLWindow::SDLWindow(const std::string& title, int width, int height)
    : width{width},
      height{height},
      sdl_window{SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE)},
      sdl_renderer{SDL_CreateRenderer(sdl_window.get(), nullptr)} {

    if (width <= 0) {
        throw exceptions::SystemException{"Window width should be positive"};
    }

    if (height <= 0) {
        throw exceptions::SystemException{"Window height should be positive"};
    }

    if (!sdl_window) {
        throw exceptions::SystemException{
            std::string{"Could not create SDL_Window: "} + SDL_GetError()
        };
    }

    if (!sdl_renderer) {
        throw exceptions::SystemException{
            std::string{"Could not create SDL_Renderer: "} + SDL_GetError()
        };
    }
}

[[nodiscard]] SDL_Renderer* SDLWindow::get_sdl_renderer() noexcept {
    return sdl_renderer.get();
}

} // namespace game
