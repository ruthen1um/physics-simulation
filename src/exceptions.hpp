#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace game::exceptions {

class SystemException: public std::exception {
private:
    std::string message;

public:
    SystemException(const std::string& message);
    [[nodiscard]] virtual const char* what() const noexcept override;
};

class ArgumentException: public std::exception {
private:
    std::string message;

public:
    ArgumentException(const std::string& message);
    [[nodiscard]] virtual const char* what() const noexcept override;
};

} // namespace game::exceptions

#endif // EXCEPTIONS_HPP
