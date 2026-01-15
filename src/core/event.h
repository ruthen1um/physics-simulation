#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include "input.h"

#include <functional>
#include <variant>

namespace game::core {

struct MouseButtonEvent {
    MouseButton button;
    MouseButtonState state;
    MousePos pos;
};

struct MouseMotionEvent {
    MousePos pos;
};

struct KeyEvent {
    Key key;
    KeyState state;
};

using Event = std::variant<MouseButtonEvent, MouseMotionEvent, KeyEvent>;

using EventHandler = std::function<void(const Event&)>;

} // namespace game::core

#endif // CORE_EVENT_H
