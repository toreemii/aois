#include <string>
#include <map>
#include <stack>

class OPZ
{
    friend int main();

public:
    static std::string toPostfix(const std::string &infix);
    static bool evaluate(const std::string &postfix, std::map<char, bool> &values);

private:
    static int getPriority(char op);
};
