#include "constants.h"
#include "objects/object.h"
#include "objects/rectangle.h"
#include "vector.h"
#include "window.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

namespace game {

void clamp_to_window(objects::Object2D& obj, float width, float height) {
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
    Game(SDLWindow& window, float fps)
        : m_window{window}, m_fps{fps} {
        if (fps <= 0.0f) {
            throw std::invalid_argument{"fps value can't be negative"};
        }

        run();
    }

    void run() {
        const auto dt = 1.0f / m_fps;

        while (m_running) {
            const auto start = SDL_GetTicks();

            input();
            update(dt);

            const auto end = SDL_GetTicks();
            const auto delta = static_cast<float>(end - start) / 1000.0f;

            if (delta < dt) {
                SDL_Delay(static_cast<Uint32>((dt - delta) * 1000.0f));
            }

            render();
        }
    }

    void input() {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_EVENT_QUIT) {
                m_running = false;
            } else if (ev.type == SDL_EVENT_WINDOW_RESIZED) {
                m_window.m_width = ev.window.data1;
                m_window.m_height = ev.window.data2;
            } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
                       ev.button.button == SDL_BUTTON_LEFT) {
                const auto x = ev.button.x;
                const auto y = ev.button.y;
                m_selected_obj = std::make_unique<objects::Rectangle>(x, y, 10, 10);
                m_selected_obj->ang_vel(-2.0f);
                clamp_to_window(
                    *m_selected_obj, static_cast<float>(m_window.m_width),
                    static_cast<float>(m_window.m_height)
                );
            } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_UP &&
                       ev.button.button == SDL_BUTTON_LEFT) {
                m_selected_obj->acc({0.0f, constants::GRAVITY});
                m_objects.push_back(std::move(m_selected_obj));
            } else if (m_selected_obj && ev.type == SDL_EVENT_MOUSE_MOTION) {
                const auto x = ev.motion.x;
                const auto y = ev.motion.y;
                m_selected_obj->pos({x, y});
                clamp_to_window(
                    *m_selected_obj, static_cast<float>(m_window.m_width),
                    static_cast<float>(m_window.m_height)
                );
            } else if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.scancode == SDL_SCANCODE_BACKSPACE) {
                m_objects.clear();
            }
        }
    }

    void update(float dt) {
        std::for_each(m_objects.begin(), m_objects.end(), [dt](auto& obj) { obj->update(dt); });

        if (m_selected_obj) {
            m_selected_obj->update(dt);
        }

        std::for_each(m_objects.begin(), m_objects.end(), [this](auto& obj) {
            const auto window_top_y = 0.0f;
            const auto window_bottom_y = static_cast<float>(m_window.m_height);
            const auto window_left_x = 0.0f;
            const auto window_right_x = static_cast<float>(m_window.m_width);

            const auto obj_top_y = obj->top().y;
            const auto obj_bottom_y = obj->bottom().y;
            const auto obj_left_x = obj->left().x;
            const auto obj_right_x = obj->right().x;

            auto pos = obj->pos();
            auto vel = obj->vel();

            if (obj_bottom_y >= window_bottom_y) {
                const auto diff = obj_bottom_y - window_bottom_y;
                pos.y -= diff;
                vel.y *= -constants::RESTITUTION;
                vel.x *= constants::GROUND_FRICTION_VALUE;
            } else if (obj_top_y <= window_top_y) {
                const auto diff = window_top_y - obj_top_y;
                pos.y += diff;
                vel.y *= -constants::RESTITUTION;
            }

            if (obj_left_x <= window_left_x) {
                const auto diff = window_left_x - obj_left_x;
                pos.x += diff;
                vel.x *= -constants::RESTITUTION;
            } else if (obj_right_x >= window_right_x) {
                const auto diff = obj_right_x - window_right_x;
                pos.x -= diff;
                vel.x *= -constants::RESTITUTION;
            }

            obj->pos(pos);
            obj->vel(vel);
        });
    }

    void render() {
        m_window.clear({0x00, 0x00, 0x00, 0xff});

        std::for_each(m_objects.begin(), m_objects.end(), [this](const auto& obj) {
            render_object(m_window, *obj);
        });

        if (m_selected_obj) {
            render_object(m_window, *m_selected_obj);
        }

        m_window.present();
    }

private:
    SDLWindow& m_window;
    std::vector<std::unique_ptr<objects::Object2D>> m_objects;

    float m_fps;

    bool m_running{true};
    std::unique_ptr<objects::Object2D> m_selected_obj{};
};

} // namespace game

int main() {
#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::err);
#endif

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        spdlog::error("Could not init SDL: {}", SDL_GetError());
        return 1;
    }

    const auto title{"Physics Simulation"};
    const auto width{16 * 50};
    const auto height{9 * 50};
    const auto fps{60.0f};

    auto window = game::SDLWindow{title, width, height};
    try {
        auto game = game::Game{window, fps};
    } catch (const std::invalid_argument& ia) {
        spdlog::error("Invalid argument: {}", ia.what());
        return 1;
    }

    SDL_Quit();

    return 0;
}
