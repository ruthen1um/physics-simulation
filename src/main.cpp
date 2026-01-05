#include "core/constants.h"
#include "core/vec.h"
#include "graphics/i_renderer.h"
#include "graphics/sdl_renderer.h"
#include "graphics/sdl_window.h"
#include "objects/object.h"
#include "objects/rectangle.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

namespace game {

void render_object(
    graphics::IRenderer& renderer, const objects::Object2& obj, [[maybe_unused]] bool fill = true
) noexcept {
    const auto vertices = obj.get_vertices_global();
    auto begin = vertices.cbegin();
    auto end = vertices.cend();
    for (auto it = begin; it != end && std::next(it) != end; ++it) {
        auto v1 = *it;
        auto v2 = *std::next(it);
        renderer.render_line(v1, v2, obj.color());
    }
    renderer.render_line(*std::prev(end), *begin, obj.color());
}

void clamp_to_window(objects::Object2& obj, float width, float height) noexcept {
    const auto obj_pos = obj.pos();
    const auto top_diff = std::abs(obj_pos.y - obj.top().y);
    const auto bottom_diff = std::abs(obj_pos.y - obj.bottom().y);
    const auto left_diff = std::abs(obj_pos.x - obj.left().x);
    const auto right_diff = std::abs(obj_pos.x - obj.right().x);

    const auto top_bound = 0.0f + top_diff;
    const auto bottom_bound = height - bottom_diff;
    const auto left_bound = 0.0f + left_diff;
    const auto right_bound = width - right_diff;

    const auto x = std::clamp(obj_pos.x, left_bound, right_bound);
    const auto y = std::clamp(obj_pos.y, top_bound, bottom_bound);

    obj.pos({x, y});
}

class Game {
public:
    Game(graphics::IWindow& window, graphics::IRenderer& renderer, float fps)
        : m_window{window}, m_renderer{renderer}, m_fps{fps} {
        if (fps <= 0.0f) {
            throw std::invalid_argument{"fps value can't be negative"};
        }

        m_window.set_event_handler(core::EventType::KeyEvent, [&](const core::EventData& data) {
            auto ev = std::get<core::KeyEventData>(data);
            if (ev.state == core::KeyState::Down && ev.key == core::Key::Backspace) {
                m_objects.clear();
            }
        });

        m_window.set_event_handler(
            core::EventType::MouseButtonEvent, [&](const core::EventData& data) {
                auto ev = std::get<core::MouseButtonEventData>(data);
                if (ev.button == core::MouseButton::Left) {
                    if (ev.state == core::MouseButtonState::Down) {
                        m_selected_obj =
                            std::make_unique<objects::Rectangle>(ev.pos.x, ev.pos.y, 10, 10);
                        m_selected_obj->ang_vel(-2.0f);
                        clamp_to_window(
                            *m_selected_obj, static_cast<float>(m_window.width()),
                            static_cast<float>(m_window.height())
                        );
                    } else {
                        m_selected_obj->acc({0.0f, core::constants::GRAVITY});
                        m_objects.push_back(std::move(m_selected_obj));
                    }
                }
            }
        );

        m_window.set_event_handler(
            core::EventType::MouseMotionEvent, [&](const core::EventData& data) {
                auto ev = std::get<core::MouseMotionEventData>(data);
                if (m_selected_obj) {
                    m_selected_obj->pos(
                        {static_cast<float>(ev.pos.x), static_cast<float>(ev.pos.y)}
                    );
                    clamp_to_window(
                        *m_selected_obj, static_cast<float>(m_window.width()),
                        static_cast<float>(m_window.height())
                    );
                }
            }
        );

        run();
    }

    void run() {
        const auto dt = 1.0f / m_fps;

        while (!m_window.should_close()) {
            const auto start = SDL_GetTicks();

            m_window.poll_events();
            update(dt);

            const auto end = SDL_GetTicks();
            const auto delta = static_cast<float>(end - start) / 1000.0f;

            if (delta < dt) {
                SDL_Delay(static_cast<Uint32>((dt - delta) * 1000.0f));
            }

            render();
        }
    }

    void update(float dt) {
        std::for_each(m_objects.begin(), m_objects.end(), [dt](auto& obj) { obj->update(dt); });

        if (m_selected_obj) {
            m_selected_obj->update(dt);
        }

        std::for_each(m_objects.begin(), m_objects.end(), [this](auto& obj) {
            const auto window_top_y = 0.0f;
            const auto window_bottom_y = static_cast<float>(m_window.height());
            const auto window_left_x = 0.0f;
            const auto window_right_x = static_cast<float>(m_window.width());

            const auto obj_top_y = obj->top().y;
            const auto obj_bottom_y = obj->bottom().y;
            const auto obj_left_x = obj->left().x;
            const auto obj_right_x = obj->right().x;

            auto pos = obj->pos();
            auto vel = obj->vel();

            if (obj_bottom_y >= window_bottom_y) {
                const auto diff = obj_bottom_y - window_bottom_y;
                pos.y -= diff;
                vel.y *= -core::constants::RESTITUTION;
                vel.x *= core::constants::GROUND_FRICTION_VALUE;
            } else if (obj_top_y <= window_top_y) {
                const auto diff = window_top_y - obj_top_y;
                pos.y += diff;
                vel.y *= -core::constants::RESTITUTION;
            }

            if (obj_left_x <= window_left_x) {
                const auto diff = window_left_x - obj_left_x;
                pos.x += diff;
                vel.x *= -core::constants::RESTITUTION;
            } else if (obj_right_x >= window_right_x) {
                const auto diff = obj_right_x - window_right_x;
                pos.x -= diff;
                vel.x *= -core::constants::RESTITUTION;
            }

            obj->pos(pos);
            obj->vel(vel);
        });
    }

    void render() {
        m_renderer.clear({0x00, 0x00, 0x00, 0xff});

        std::for_each(m_objects.begin(), m_objects.end(), [this](const auto& obj) {
            render_object(m_renderer, *obj);
        });

        if (m_selected_obj) {
            render_object(m_renderer, *m_selected_obj);
        }

        m_renderer.present();
    }

private:
    graphics::IWindow& m_window;
    graphics::IRenderer& m_renderer;
    std::vector<std::unique_ptr<objects::Object2>> m_objects;

    float m_fps;
    std::unique_ptr<objects::Object2> m_selected_obj{};
};

} // namespace game

int main() {
#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::err);
#endif

    const auto title{"Physics Simulation"};
    const auto width{16 * 50};
    const auto height{9 * 50};
    const auto fps{60.0f};

    auto window = game::graphics::SDLWindow{title, width, height};
    auto renderer = game::graphics::SDLRenderer{window};

    try {
        auto game = game::Game{window, renderer, fps};
    } catch (const std::invalid_argument& ia) {
        spdlog::error("Invalid argument: {}", ia.what());
        return 1;
    } catch (const std::runtime_error& re) {
        spdlog::error("Runtime error: {}", re.what());
        return 2;
    }

    return 0;
}
