#include "exceptions.hpp"
#include "object.hpp"
#include "objects/rectangle.hpp"
#include "vector.hpp"
#include "window.hpp"

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <memory>
#include <vector>

namespace game {

constexpr float GRAVITY = 9.8f * 100;
constexpr float RESTITUTION = 0.3f;
constexpr float GROUND_FRICTION_VALUE = 0.9f;

void debug_show_box(SDL_Renderer* renderer, const Object2D& obj) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    auto v1 = Vector2D{obj.left_x(), obj.top_y()};
    auto v2 = Vector2D{obj.right_x(), obj.top_y()};
    auto v3 = Vector2D{obj.right_x(), obj.bottom_y()};
    auto v4 = Vector2D{obj.left_x(), obj.bottom_y()};
    SDL_RenderLine(renderer, v1.x, v1.y, v2.x, v2.y);
    SDL_RenderLine(renderer, v2.x, v2.y, v3.x, v3.y);
    SDL_RenderLine(renderer, v3.x, v3.y, v4.x, v4.y);
    SDL_RenderLine(renderer, v4.x, v4.y, v1.x, v1.y);
}

void clamp_to_window(Object2D& obj, float width, float height) {
    const auto top_diff = std::abs(obj.pos.y - obj.top_y());
    const auto bottom_diff = std::abs(obj.pos.y - obj.bottom_y());
    const auto left_diff = std::abs(obj.pos.x - obj.left_x());
    const auto right_diff = std::abs(obj.pos.x - obj.right_x());

    const auto top_bound = 0.0f + top_diff;
    const auto bottom_bound = height - bottom_diff;
    const auto left_bound = 0.0f + left_diff;
    const auto right_bound = width - right_diff;

    const auto x = std::clamp(obj.pos.x, left_bound, right_bound);
    const auto y = std::clamp(obj.pos.y, top_bound, bottom_bound);

    obj.pos = Vector2D{x, y};
}

class Game {
public:
    SDLWindow& window;
    std::vector<std::unique_ptr<Object2D>> objects;

    float fps;

    bool running{true};
    bool show_boxes{false};
    std::unique_ptr<Object2D> selected_obj{};

    explicit Game(SDLWindow& window, float fps)
        : window{window}, fps{fps} {
        if (fps <= 0.0f) {
            throw exceptions::ArgumentException{"fps value can't be negative"};
        }

        run();
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
                clamp_to_window(
                    *selected_obj, static_cast<float>(window.width),
                    static_cast<float>(window.height)
                );
            } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                selected_obj->acc.y = GRAVITY;
                objects.push_back(std::move(selected_obj));
            } else if (selected_obj && ev.type == SDL_EVENT_MOUSE_MOTION) {
                const auto x = ev.motion.x;
                const auto y = ev.motion.y;
                selected_obj->pos = Vector2D{x, y};
                clamp_to_window(
                    *selected_obj, static_cast<float>(window.width),
                    static_cast<float>(window.height)
                );
            } else if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.scancode == SDL_SCANCODE_ESCAPE) {
                show_boxes = !show_boxes;
            }
        }
    }

    void update(float dt) {
        std::for_each(objects.begin(), objects.end(), [dt](auto& obj) { obj->update(dt); });

        std::for_each(objects.begin(), objects.end(), [this](auto& obj) {
            const auto window_top_y = 0.0f;
            const auto window_bottom_y = static_cast<float>(window.height);
            const auto window_left_x = 0.0f;
            const auto window_right_x = static_cast<float>(window.width);

            const auto obj_top_y = obj->top_y();
            const auto obj_bottom_y = obj->bottom_y();
            const auto obj_left_x = obj->left_x();
            const auto obj_right_x = obj->right_x();

            if (obj_bottom_y >= window_bottom_y) {
                auto diff = obj_bottom_y - window_bottom_y;
                obj->pos.y -= diff;
                obj->vel.y *= -RESTITUTION;
                obj->vel.x *= GROUND_FRICTION_VALUE;
            } else if (obj_top_y <= window_top_y) {
                auto diff = window_top_y - obj_top_y;
                obj->pos.y += diff;
                obj->vel.y *= -RESTITUTION;
            }

            if (obj_left_x <= window_left_x) {
                auto diff = window_left_x - obj_left_x;
                obj->pos.x += diff;
                obj->vel.x *= -RESTITUTION;
            } else if (obj_right_x >= window_right_x) {
                auto diff = obj_right_x - window_right_x;
                obj->pos.x -= diff;
                obj->vel.x *= -RESTITUTION;
            }
        });
    }

    void render() {
        auto renderer = window.get_sdl_renderer();

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(renderer);

        std::for_each(objects.begin(), objects.end(), [this, renderer](const auto& obj) {
            obj->render(renderer);
            if (show_boxes) {
                debug_show_box(renderer, *obj);
            }
        });

        if (selected_obj) {
            selected_obj->render(renderer);
            if (show_boxes) {
                debug_show_box(renderer, *selected_obj);
            }
        }

        SDL_RenderPresent(renderer);
    }

private:
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
