#include "constants.h"
#include "exceptions.h"
#include "object.h"
#include "objects/rectangle.h"
#include "vector.h"
#include "window.h"

#include <algorithm>
#include <memory>
#include <vector>

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

namespace game {

void clamp_to_window(Object2D& obj, float width, float height) {
    const auto top_diff = std::abs(obj.pos.y - obj.top().y);
    const auto bottom_diff = std::abs(obj.pos.y - obj.bottom().y);
    const auto left_diff = std::abs(obj.pos.x - obj.left().x);
    const auto right_diff = std::abs(obj.pos.x - obj.right().x);

    const auto top_bound = 0.0f + top_diff;
    const auto bottom_bound = height - bottom_diff;
    const auto left_bound = 0.0f + left_diff;
    const auto right_bound = width - right_diff;

    const auto x = std::clamp(obj.pos.x, left_bound, right_bound);
    const auto y = std::clamp(obj.pos.y, top_bound, bottom_bound);

    obj.pos = {x, y};
}

class Game {
public:
    SDLWindow& window;
    std::vector<std::unique_ptr<Object2D>> objects;

    float fps;

    bool running{true};
    std::unique_ptr<Object2D> selected_obj{};

    Game(SDLWindow& window, float fps)
        : window{window}, fps{fps} {
        if (fps <= 0.0f) {
            throw exceptions::ArgumentException{"fps value can't be negative"};
        }

        run();
    }

    void run() {
        const auto dt = 1.0f / fps;

        while (running) {
            auto start = SDL_GetTicks();

            input();
            update(dt);

            auto end = SDL_GetTicks();
            auto delta = static_cast<float>(end - start) / 1000.0f;

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
                running = false;
            } else if (ev.type == SDL_EVENT_WINDOW_RESIZED) {
                window.width = ev.window.data1;
                window.height = ev.window.data2;
            } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                const auto x = ev.button.x;
                const auto y = ev.button.y;
                selected_obj = std::make_unique<objects::Rectangle>(x, y, 10, 10);
                selected_obj->rotating = true;
                clamp_to_window(
                    *selected_obj, static_cast<float>(window.width),
                    static_cast<float>(window.height)
                );
            } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                selected_obj->acc.y = constants::GRAVITY;
                objects.push_back(std::move(selected_obj));
            } else if (selected_obj && ev.type == SDL_EVENT_MOUSE_MOTION) {
                const auto x = ev.motion.x;
                const auto y = ev.motion.y;
                selected_obj->pos = {x, y};
                clamp_to_window(
                    *selected_obj, static_cast<float>(window.width),
                    static_cast<float>(window.height)
                );
            } else if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.scancode == SDL_SCANCODE_BACKSPACE) {
                objects.clear();
            }
        }
    }

    void update(float dt) {
        std::for_each(objects.begin(), objects.end(), [dt](auto& obj) { obj->update(dt); });

        if (selected_obj) {
            selected_obj->update(dt);
        }

        std::for_each(objects.begin(), objects.end(), [this](auto& obj) {
            bool touch{false};
            const auto window_top_y = 0.0f;
            const auto window_bottom_y = static_cast<float>(window.height);
            const auto window_left_x = 0.0f;
            const auto window_right_x = static_cast<float>(window.width);

            const auto obj_top_y = obj->top().y;
            const auto obj_bottom_y = obj->bottom().y;
            const auto obj_left_x = obj->left().x;
            const auto obj_right_x = obj->right().x;

            if (obj_bottom_y >= window_bottom_y) {
                touch = true;
                auto diff = obj_bottom_y - window_bottom_y;
                obj->pos.y -= diff;
                obj->vel.y *= -constants::RESTITUTION;
                obj->vel.x *= constants::GROUND_FRICTION_VALUE;
            }

            if (obj_top_y <= window_top_y) {
                touch = true;
                auto diff = window_top_y - obj_top_y;
                obj->pos.y += diff;
                obj->vel.y *= -constants::RESTITUTION;
            }

            if (obj_left_x <= window_left_x) {
                touch = true;
                auto diff = window_left_x - obj_left_x;
                obj->pos.x += diff;
                obj->vel.x *= -constants::RESTITUTION;
            }

            if (obj_right_x >= window_right_x) {
                touch = true;
                auto diff = obj_right_x - window_right_x;
                obj->pos.x -= diff;
                obj->vel.x *= -constants::RESTITUTION;
            }

            if (touch) {
                obj->rotating = false;
            }
        });
    }

    void render() {
        window.render_bg({0x00, 0x00, 0x00, 0xff});

        std::for_each(objects.begin(), objects.end(), [this](const auto& obj) {
            window.render(*obj);
        });

        if (selected_obj) {
            window.render(*selected_obj);
        }

        window.present();
    }
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
    game::Game{window, fps};

    SDL_Quit();

    return 0;
}
