#ifndef OBJECT_H
#define OBJECT_H

#include "color.h"
#include "vector.h"

#include <vector>

#include <SDL3/SDL.h>

namespace game {

class IObject2D {
public:
    virtual void update(float dt) noexcept = 0;

    [[nodiscard]] virtual std::vector<Vector2D> get_vertices_global() const noexcept = 0;
    [[nodiscard]] virtual std::vector<Vector2D> get_vertices_local() const noexcept = 0;

    [[nodiscard]] virtual Vector2D top() const noexcept = 0;
    [[nodiscard]] virtual Vector2D right() const noexcept = 0;
    [[nodiscard]] virtual Vector2D bottom() const noexcept = 0;
    [[nodiscard]] virtual Vector2D left() const noexcept = 0;

protected:
    virtual ~IObject2D() = default;
    IObject2D() = default;
};

class Object2D : public IObject2D {
public:
    Vector2D pos;
    Vector2D vel;
    Vector2D acc;
    Color color;
    float angle{0.0f};
    bool rotating{false};

    Object2D(Vector2D pos);

    virtual void update(float dt) noexcept override;
};

} // namespace game

#endif // OBJECT_H
