#ifndef CORE_INPUT_H
#define CORE_INPUT_H

namespace game::core {

enum class Key { Unknown, Escape, Backspace };
enum class MouseButton { Unknown, Left, Middle, Right };

enum class KeyState { Up, Down };
enum class MouseButtonState { Up, Down };

struct MousePos {
    int x;
    int y;
};

} // namespace game::core

#endif // CORE_INPUT_H
