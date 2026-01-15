#ifndef CORE_GAME_H
#define CORE_GAME_H

#include <optional>
#include <vector>

#include "core/renderer.h"
#include "core/window.h"
#include "objects/polygon.h"

namespace game::core {
class IRenderer;
class IWindow;
} // namespace game::core

namespace game::core {

class Game {
public:
    Game(core::IWindow& window, core::IRenderer& renderer, float fps);
    void run();

private:
    void input();
    void update(float dt);
    void render();

    core::IWindow& m_window;
    core::IRenderer& m_renderer;
    float m_fps;

    std::vector<objects::Quad> m_quads;
    std::optional<objects::Quad> m_selected_quad;
};

} // namespace game::core

#endif // CORE_GAME_H
