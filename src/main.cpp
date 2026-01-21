#include <fmt/base.h>
#include <fmt/format.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <string>

#include "backends/sdl/renderer.h"
#include "backends/sdl/window.h"
#include "core/game.h"

int main() {
#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::err);
#endif

    const auto title = "Physics Simulation";
    const auto width = 16 * 50;
    const auto height = 9 * 50;
    const auto fps = 60.0f;

    auto window = game::backends::sdl::SDLWindow{title, width, height};
    auto renderer = game::backends::sdl::SDLRenderer{window};

    try {
        auto game = game::core::Game{window, renderer, fps};
        game.run();
    } catch (const std::invalid_argument& ia) {
        spdlog::error("Invalid argument: {}", ia.what());
        return 1;
    } catch (const std::runtime_error& re) {
        spdlog::error("Runtime error: {}", re.what());
        return 2;
    }

    return 0;
}
