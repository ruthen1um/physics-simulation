#include "core/game.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <optional>
#include <stdexcept>
#include <thread>
#include <utility>
#include <variant>
#include <vector>

#include "core/collision.h"
#include "core/color.h"
#include "core/constants.h"
#include "core/event.h"
#include "core/input.h"
#include "core/math.h"
#include "core/renderer.h"
#include "core/window.h"
#include "objects/polygon.h"

namespace game::core {

template <std::size_t N>
void clamp_to_window(objects::Polygon<N>& poly, float width, float height) noexcept {
    const auto verts = poly.get_vertices_world();
    const auto top = get_uppermost_vertex(verts);
    const auto bottom = get_lowermost_vertex(verts);
    const auto left = get_leftmost_vertex(verts);
    const auto right = get_rightmost_vertex(verts);
    const auto pos = poly.get_pos();

    const auto top_diff = std::abs(pos.y - top.y);
    const auto bottom_diff = std::abs(pos.y - bottom.y);
    const auto left_diff = std::abs(pos.x - left.x);
    const auto right_diff = std::abs(pos.x - right.x);

    const auto top_bound = 0.0f + top_diff;
    const auto bottom_bound = height - bottom_diff;
    const auto left_bound = 0.0f + left_diff;
    const auto right_bound = width - right_diff;

    const auto x = std::clamp(pos.x, left_bound, right_bound);
    const auto y = std::clamp(pos.y, top_bound, bottom_bound);

    poly.set_pos({x, y});
}

Game::Game(core::IWindow& window, core::IRenderer& renderer, float fps)
    : m_window{window}, m_renderer{renderer}, m_fps{fps} {

    if (fps <= 0.0f) {
        throw std::invalid_argument{"fps value can't be negative"};
    }

    const auto handle_key = [this](const KeyEvent& ev) {
        if (ev.state == KeyState::Down && ev.key == Key::Backspace) {
            m_quads.clear();
        }
    };

    const auto handle_mouse_button = [this](const MouseButtonEvent& ev) {
        if (ev.button == MouseButton::Left) {
            if (ev.state == MouseButtonState::Down) {
                const auto x = static_cast<float>(ev.pos.x);
                const auto y = static_cast<float>(ev.pos.y);
                const auto w = 10;
                const auto h = 10;
                const auto c = core::Color{0xff, 0xff, 0xff, 0xff};

                m_selected_quad = objects::Quad::rectangle(x, y, w, h, c);

                m_selected_quad->set_ang_vel(-2.0f);
                clamp_to_window(
                    *m_selected_quad, static_cast<float>(m_window.get_width()),
                    static_cast<float>(m_window.get_height())
                );
            } else {
                m_selected_quad->set_acc({0.0f, GRAVITY});
                m_quads.push_back(*std::exchange(m_selected_quad, std::nullopt));
            }
        }
    };

    const auto handle_mouse_motion = [this](const MouseMotionEvent& ev) {
        if (m_selected_quad) {
            m_selected_quad->set_pos({static_cast<float>(ev.pos.x), static_cast<float>(ev.pos.y)});
            clamp_to_window(
                *m_selected_quad, static_cast<float>(m_window.get_width()),
                static_cast<float>(m_window.get_height())
            );
        }
    };

    const auto event_handler =
        [handle_key = std::move(handle_key), handle_mouse_button = std::move(handle_mouse_button),
         handle_mouse_motion = std::move(handle_mouse_motion)](const Event& ev) {
            if (auto* e = std::get_if<KeyEvent>(&ev)) {
                handle_key(*e);
            } else if (auto* e = std::get_if<MouseButtonEvent>(&ev)) {
                handle_mouse_button(*e);
            } else if (auto* e = std::get_if<MouseMotionEvent>(&ev)) {
                handle_mouse_motion(*e);
            }
        };

    m_window.set_event_handler(event_handler);
}

void Game::run() {
    const auto dt = 1.0f / m_fps;
    const auto frame_time = std::chrono::duration<float>(dt);

    using Clock = std::chrono::system_clock;

    while (!m_window.should_close()) {
        const auto start = Clock::now();

        input();
        update(dt);
        render();

        const auto end = Clock::now();
        const auto work_time = end - start;
        if (work_time < frame_time) {
            std::this_thread::sleep_for(frame_time - work_time);
        }
    }
}

void Game::input() {
    m_window.poll_events();
}

void Game::update(float dt) {
    for (auto& quad : m_quads) {
        quad.integrate(dt);
    }

    if (m_selected_quad) {
        m_selected_quad->integrate(dt);
    }

    for (auto& quad : m_quads) {
        const auto window_top_y = 0.0f;
        const auto window_bottom_y = static_cast<float>(m_window.get_height());
        const auto window_left_x = 0.0f;
        const auto window_right_x = static_cast<float>(m_window.get_width());

        const auto vertices = quad.get_vertices_world();

        const auto obj_top_y = get_uppermost_vertex(vertices).y;
        const auto obj_bottom_y = get_lowermost_vertex(vertices).y;
        const auto obj_left_x = get_leftmost_vertex(vertices).x;
        const auto obj_right_x = get_rightmost_vertex(vertices).x;

        auto pos = quad.get_pos();
        auto vel = quad.get_vel();

        if (obj_bottom_y >= window_bottom_y) {
            const auto diff = obj_bottom_y - window_bottom_y;
            pos.y -= diff;
            vel.y *= -RESTITUTION;
            vel.x *= GROUND_FRICTION_VALUE;
        } else if (obj_top_y <= window_top_y) {
            const auto diff = window_top_y - obj_top_y;
            pos.y += diff;
            vel.y *= -RESTITUTION;
        }

        if (obj_left_x <= window_left_x) {
            const auto diff = window_left_x - obj_left_x;
            pos.x += diff;
            vel.x *= -RESTITUTION;
        } else if (obj_right_x >= window_right_x) {
            const auto diff = obj_right_x - window_right_x;
            pos.x -= diff;
            vel.x *= -RESTITUTION;
        }

        quad.set_pos(pos);
        quad.set_vel(vel);
    };
}

void Game::render() {
    m_renderer.clear({0x00, 0x00, 0x00, 0xff});

    for (const auto& quad : m_quads) {
        quad.render(m_renderer);
    }

    if (m_selected_quad) {
        m_selected_quad->render(m_renderer);
    }

    m_renderer.present();
}

} // namespace game::core
