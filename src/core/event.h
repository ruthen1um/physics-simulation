#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include "input.h"

#include <functional>
#include <variant>

namespace game::core {

struct MouseButtonEventData {
    MouseButton button;
    MouseButtonState state;
    MousePos pos;
};

struct MouseMotionEventData {
    MousePos pos;
};

struct KeyEventData {
    Key key;
    KeyState state;
};

enum class EventType { MouseButtonEvent, MouseMotionEvent, KeyEvent };

using EventData = std::variant<MouseButtonEventData, MouseMotionEventData, KeyEventData>;

using EventHandler = std::function<void(const EventData&)>;

} // namespace game::core

#endif // CORE_EVENT_H
