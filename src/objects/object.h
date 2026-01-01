#ifndef OBJECT_H
#define OBJECT_H

#include "../color.h"
#include "../vector.h"

#include <vector>

#include <SDL3/SDL.h>

namespace game::objects {

class IObject2D {
public:
    IObject2D() = default;
    virtual ~IObject2D() = default;

    IObject2D(const IObject2D&) = delete;
    IObject2D& operator=(const IObject2D&) = delete;
    IObject2D(IObject2D&&) = delete;
    IObject2D& operator=(IObject2D&&) = delete;

    virtual void update(float dt) noexcept = 0;

    [[nodiscard]] virtual std::vector<Vector2D> get_vertices_global() const noexcept = 0;
    [[nodiscard]] virtual std::vector<Vector2D> get_vertices_local() const noexcept = 0;

    [[nodiscard]] virtual Vector2D top() const noexcept = 0;
    [[nodiscard]] virtual Vector2D right() const noexcept = 0;
    [[nodiscard]] virtual Vector2D bottom() const noexcept = 0;
    [[nodiscard]] virtual Vector2D left() const noexcept = 0;
};

class Object2D : public IObject2D {
public:
    Vector2D m_pos;
    Vector2D m_vel;
    Vector2D m_acc;
    Color m_color;
    float m_angle{0.0f};
    float m_ang_vel{0.0f};

    Object2D(Vector2D pos) noexcept;

    void update(float dt) noexcept override;

    [[nodiscard]] Vector2D pos() const noexcept;
    void pos(Vector2D pos) noexcept;

    [[nodiscard]] Vector2D vel() const noexcept;
    void vel(Vector2D vel) noexcept;

    [[nodiscard]] Vector2D acc() const noexcept;
    void acc(Vector2D acc) noexcept;

    [[nodiscard]] Color color() const noexcept;
    void color(Color color) noexcept;

    [[nodiscard]] float ang_vel() const noexcept;
    void ang_vel(float ang_vel) noexcept;
};

} // namespace game::objects

#endif // OBJECT_H
