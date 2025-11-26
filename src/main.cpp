#include "vector.hpp"
#include "object.hpp"
#include "objects/rectangle.hpp"
#include "exceptions.hpp"

#include <SDL3/SDL.h>

#include <algorithm>
#include <memory>
#include <vector>

namespace game {

constexpr float GRAVITY = 9.8f * 100;
constexpr float RESTITUTION = 0.3f;
constexpr float GROUND_FRICTION_VALUE = 0.9f;

void debug_show_box(SDL_Renderer* renderer, const Object2D& obj) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    auto v1 = Vector2D{obj.left(), obj.top()};
    auto v2 = Vector2D{obj.right(), obj.top()};
    auto v3 = Vector2D{obj.right(), obj.bottom()};
    auto v4 = Vector2D{obj.left(), obj.bottom()};
    SDL_RenderLine(renderer, v1.x, v1.y, v2.x, v2.y);
    SDL_RenderLine(renderer, v2.x, v2.y, v3.x, v3.y);
    SDL_RenderLine(renderer, v3.x, v3.y, v4.x, v4.y);
    SDL_RenderLine(renderer, v4.x, v4.y, v1.x, v1.y);
}

bool intersects(const Object2D& a, const Object2D& b) noexcept {
    return !(a.right() <= b.left() ||
             a.left() >= b.right() ||
             a.bottom() <= b.top() ||
             a.top() >= b.bottom());
}

class Game {
private:
    class WindowDeleter {
    public:
        void operator()(SDL_Window* window) const noexcept {
            if (window) {
                SDL_DestroyWindow(window);
            }
        }
    };

    class RendererDeleter {
    public:
        void operator()(SDL_Renderer* renderer) const noexcept {
            if (renderer) {
                SDL_DestroyRenderer(renderer);
            }
        }
    };

public:
    std::unique_ptr<SDL_Window, WindowDeleter> window;
    std::unique_ptr<SDL_Renderer, RendererDeleter> renderer;
    std::vector<std::unique_ptr<Object2D>> objects;
    bool running;
    float fps;

    Game(const std::string& title, const int width, const int height, const float fps)
        : window{SDL_CreateWindow(title.c_str(), width, height, 0)},
          renderer{SDL_CreateRenderer(window.get(), nullptr)}, running{true}, fps{fps} {
        if (!window) {
            throw exceptions::SystemException{std::string{"Could not create window: "} + SDL_GetError()};
        }

        if (!renderer) {
            throw exceptions::SystemException{std::string{"Could not create renderer: "} + SDL_GetError()};
        }

        if (fps <= 0.0f) {
            throw exceptions::ArgumentException{"fps value can't be negative"};
        }
    }

    void input() {

    }

    void update() {

    }

    void render() {

    }

    void run() {
        const auto dt = 1.0f / fps;
        auto selected_obj = std::unique_ptr<Object2D>{};
        auto show_boxes = false;

        while (running) {
            auto start = SDL_GetTicks();

            SDL_Event ev;
            while (SDL_PollEvent(&ev)) {
                if (ev.type == SDL_EVENT_QUIT) {
                    running = false;
                } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                    auto x = ev.button.x;
                    auto y = ev.button.y;
                    selected_obj = std::make_unique<objects::Rectangle>(x, y, 10, 10, 10);
                } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                    selected_obj->acc.y = GRAVITY;
                    objects.push_back(std::move(selected_obj));
                } else if (ev.type == SDL_EVENT_MOUSE_MOTION) {
                    auto x = ev.motion.x;
                    auto y = ev.motion.y;
                    if (selected_obj) {
                        selected_obj->pos = Vector2D{x, y};
                    }
                } else if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.scancode == SDL_SCANCODE_ESCAPE) {
                    show_boxes = !show_boxes;
                }
            }

            std::for_each(objects.begin(), objects.end(), [&dt](auto& obj){
                obj->update(dt);
            });

            int window_width, window_height;
            SDL_GetWindowSize(window.get(), &window_width, &window_height);

            std::for_each(objects.begin(), objects.end(), [window_width, window_height](auto& obj){
                const auto window_top = 0.0f;
                const auto window_bottom = static_cast<float>(window_height);
                const auto window_left = 0.0f;
                const auto window_right = static_cast<float>(window_width);

                if (obj->bottom() >= window_bottom) {
                    auto diff = obj->bottom() - window_bottom;
                    obj->pos.y -= diff;
                    obj->vel.y *= -RESTITUTION;
                    obj->vel.x *= GROUND_FRICTION_VALUE;
                } else if (obj->top() <= window_top) {
                    auto diff = window_top - obj->top();
                    obj->pos.y += diff;
                    obj->vel.y *= -RESTITUTION;
                }

                if (obj->left() <= window_left) {
                    auto diff = window_left - obj->left();
                    obj->pos.x += diff;
                    obj->vel.x *= -RESTITUTION;
                } else if (obj->right() >= window_right) {
                    auto diff = obj->right() - window_right;
                    obj->pos.x -= diff;
                    obj->vel.x *= -RESTITUTION;
                }
            });

            for (size_t i = 0; i < objects.size(); ++i) {
                for (size_t j = i + 1; j < objects.size(); ++j) {
                    auto& a = *objects[i];
                    auto& b = *objects[j];

                    if (!intersects(a, b)) continue;
                }
            }

            auto end = SDL_GetTicks();
            auto delta = static_cast<float>(end - start) / 1000.0f;

            if (delta < dt) {
                SDL_Delay(static_cast<Uint32>((dt - delta) * 1000.0f));
            }

            auto p_renderer = renderer.get();

            SDL_SetRenderDrawColor(p_renderer, 0x00, 0x00, 0x00, 0xff);
            SDL_RenderClear(p_renderer);

            std::for_each(objects.begin(), objects.end(), [show_boxes, p_renderer](const auto& obj){
                obj->render(p_renderer);
                if (show_boxes) {
                    debug_show_box(p_renderer, *obj);
                }
            });

            if (selected_obj) {
                selected_obj->render(p_renderer);
                if (show_boxes) {
                    debug_show_box(p_renderer, *selected_obj);
                }
            }

            SDL_RenderPresent(p_renderer);
        }
    }
};

} // namespace game

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not init SDL: %s", SDL_GetError());
        return 1;
    }

    int exit_code {0};

    const int width {16 * 50};
    const int height {9 * 50};
    const float fps {60};

    try {
        auto game = game::Game{"Game", width, height, fps};
        game.run();
    } catch (const game::exceptions::SystemException& ex) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, ex.what());
        exit_code = 1;
    } catch (const game::exceptions::ArgumentException& ex) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, ex.what());
        exit_code = 2;
    }

    SDL_Quit();

    return exit_code;
}
