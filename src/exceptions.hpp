#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace game::exceptions {

class SystemException : public std::exception {
public:
    SystemException(const std::string& message);
    [[nodiscard]] virtual const char* what() const noexcept override;

private:
    std::string message;
};

class ArgumentException : public std::exception {
public:
    ArgumentException(const std::string& message);
    [[nodiscard]] virtual const char* what() const noexcept override;

private:
    std::string message;
};

} // namespace game::exceptions

#endif // EXCEPTIONS_HPP
