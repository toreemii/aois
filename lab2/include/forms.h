#include <string>
#include <vector>
#include <map>
#include <set>

struct PostClasses
{
    bool t0, t1, s, m, l;
};

struct Implicant
{
    std::vector<int> bits;
    bool used = false;

    bool operator<(const Implicant &other) const
    {
        return bits < other.bits;
    }
};

class NormalForms
{
public:
    static std::string getSDNF(const std::vector<char> &vars, const std::vector<std::map<char, bool>> &ones);
    static std::string getSKNF(const std::vector<char> &vars, const std::vector<std::map<char, bool>> &zeros);

    static std::string getNumericSDNF(const std::vector<int> &indices);
    static std::string getNumericSKNF(const std::vector<int> &indices);

    static std::string getFunctionIndex(const std::vector<bool> &results);

    static PostClasses checkPostClasses(const std::vector<bool> &results, int varCount);
    static void printPostTable(const PostClasses& p, const std::vector<bool>& res, int n);

    static std::string getZhegalkinPolynomial(const std::vector<bool> &results, const std::vector<char> &vars);

    static void findVariablesType(const std::vector<bool> &results, const std::vector<char> &vars,
                                  std::vector<char> &essential, std::vector<char> &fictitious);

    static std::vector<bool> getBooleanDerivative(const std::vector<bool> &results, int varIndex, int totalVars);
    static std::string vectorToTableString(const std::vector<bool> &derivativeRes);

    static std::string getMinimizedQuine(const std::vector<char> &vars, const std::vector<int> &ones_indices);

    static void getQuineMcCluskeyTable(const std::vector<char> &vars, const std::vector<int> &ones_i);

    static void printKarnaughMap(const std::vector<bool> &results, const std::vector<char> &vars);
};
