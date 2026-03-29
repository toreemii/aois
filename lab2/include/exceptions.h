#include <stdexcept>
#include <string>

class LogicalError : public std::runtime_error
{
public:
    LogicalError(const std::string &msg) : std::runtime_error(msg) {}
};

class InvalidSymbol : public LogicalError
{
public:
    InvalidSymbol(char c) : LogicalError("Oшибка: символ '" + std::string(1, c) + "' запрещен!") {}
};

class BracketError : public LogicalError
{
public:
    BracketError() : LogicalError("Oшибка: проверьте скобки!") {}
};