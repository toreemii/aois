#include <string>

class Table
{
public:
    static void generate(const std::string &raw_expr, int mode);

private:
    static std::string validateAndClean(const std::string &expr);
};