#include "exceptions.hpp"

#include <exception>
#include <string>

namespace game::exceptions {

SystemException::SystemException(const std::string& message): message{message} {}
[[nodiscard]] const char* SystemException::what() const noexcept {
    return message.c_str();
}

ArgumentException::ArgumentException(const std::string& message): message{message} {}
[[nodiscard]] const char* ArgumentException::what() const noexcept {
    return message.c_str();
}

} // namespace game::exceptions
