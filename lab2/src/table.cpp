#include "../include/table.h"
#include "../include/opz.h"
#include "../include/forms.h"
#include "../include/exceptions.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <stack>

std::string Table::validateAndClean(const std::string &expr)
{
    if (expr.empty())
        throw LogicalError("Строка пуста.");
    std::string res = "";
    int brackets = 0;
    for (size_t i = 0; i < expr.length(); i++)
    {
        char c = expr[i];
        if (isspace(c))
            continue;
        if (c >= 'a' && c <= 'e')
            res += c;
        else if (c == '-' && i + 1 < expr.length() && expr[i + 1] == '>')
        {
            res += '>';
            i++;
        }
        else if (std::string("!&|~()").find(c) != std::string::npos)
        {
            res += c;
            if (c == '(')
                brackets++;
            if (c == ')')
                brackets--;
        }
        else
            throw InvalidSymbol(c);
        if (brackets < 0)
            throw BracketError();
    }
    if (brackets != 0)
        throw BracketError();
    return res;
}

void Table::generate(const std::string &raw_expr, int mode)
{
    std::string formula = validateAndClean(raw_expr);
    std::string postfix = OPZ::toPostfix(formula);

    std::set<char> varSet;
    for (char c : formula)
        if (c >= 'a' && c <= 'e')
            varSet.insert(c);
    std::vector<char> vars(varSet.begin(), varSet.end());

    if (vars.empty())
        throw LogicalError("Переменные не найдены.");

    std::vector<std::map<char, bool>> ones_v, zeros_v;
    std::vector<int> ones_i, zeros_i;
    std::vector<bool> all_res;

    for (char v : vars)
        std::cout << v << "\t";
    std::cout << "| F" << std::endl;
    std::cout << "-----------------------" << std::endl;

    int rows = std::pow(2, vars.size());
    for (int i = 0; i < rows; i++)
    {
        std::map<char, bool> values;
        for (int j = 0; j < (int)vars.size(); j++)
        {
            bool val = (i >> (vars.size() - 1 - j)) & 1;
            values[vars[j]] = val;
            std::cout << val << "\t";
        }

        bool res = OPZ::evaluate(postfix, values);
        std::cout << "| " << res << std::endl;

        all_res.push_back(res);
        if (res)
        {
            ones_v.push_back(values);
            ones_i.push_back(i);
        }
        else
        {
            zeros_v.push_back(values);
            zeros_i.push_back(i);
        }
    }

    switch (mode)
    {
    case 3:
        std::cout << "\n--- Пункт 3: СДНФ и СКНФ ---" << std::endl;
        std::cout << "СДНФ: " << NormalForms::getSDNF(vars, ones_v) << std::endl;
        std::cout << "СКНФ: " << NormalForms::getSKNF(vars, zeros_v) << std::endl;
        break;
    case 4:
        std::cout << "\n--- Пункт 4: Числовая форма ---" << std::endl;
        std::cout << NormalForms::getNumericSDNF(ones_i) << std::endl;
        std::cout << NormalForms::getNumericSKNF(zeros_i) << std::endl;
        break;
    case 5:
        std::cout << "\n--- Пункт 5: Индексная форма ---" << std::endl;
        std::cout << NormalForms::getFunctionIndex(all_res) << std::endl;
        break;
    case 6:
    {
        std::cout << "\n--- Пункт 6: Классы Поста ---" << std::endl;
        PostClasses p = NormalForms::checkPostClasses(all_res, vars.size());
        // Передаем саму структуру, вектор результатов и его размер
        NormalForms::printPostTable(p, all_res, (int)all_res.size());
        break;
    }
    case 7:
        std::cout << "\n--- Пункт 7: Полином Жегалкина ---" << std::endl;
        std::cout << "P(z) = " << NormalForms::getZhegalkinPolynomial(all_res, vars) << std::endl;
        break;
    case 8:
    {
        std::vector<char> essential, fictitious;
        NormalForms::findVariablesType(all_res, vars, essential, fictitious);

        std::cout << "\n--- Анализ переменных ---" << std::endl;
        std::cout << "Существенные: ";
        if (essential.empty())
            std::cout << "нет";
        else
            for (char c : essential)
                std::cout << c << " ";

        std::cout << "\nФиктивные: ";
        if (fictitious.empty())
            std::cout << "нет";
        else
            for (char c : fictitious)
                std::cout << c << " ";
        std::cout << std::endl;
        break;
    }
    case 9:
    {
        std::cout << "\n--- Пункт 9: Булево дифференцирование ---" << std::endl;
        for (int i = 0; i < (int)vars.size(); i++)
        {
            std::vector<bool> df = NormalForms::getBooleanDerivative(all_res, i, vars.size());
            std::cout << "df/d" << vars[i] << " = " << NormalForms::vectorToTableString(df) << std::endl;
        }

        if (vars.size() >= 2)
        {
            std::vector<bool> df1 = NormalForms::getBooleanDerivative(all_res, 0, vars.size());
            std::vector<bool> d2f = NormalForms::getBooleanDerivative(df1, 1, vars.size());
            std::cout << "d2f/d" << vars[0] << "d" << vars[1] << " = " << NormalForms::vectorToTableString(d2f) << std::endl;
        }
        break;
    }
    case 10:
    {
        std::cout << "\n--- Пункт 10: Расчетная минимизация (Квайн) ---" << std::endl;
        std::string minimized = NormalForms::getMinimizedQuine(vars, ones_i);
        std::cout << "\nРезультат минимизации: " << minimized << std::endl;
        break;
    }
    case 11:
    {
        std::cout << "\n--- Пункт 11: Расчетно-табличная минимизация (Квайн-МакКласки) ---" << std::endl;
        NormalForms::getQuineMcCluskeyTable(vars, ones_i);
        break;
    }
    case 12:
    {
        std::cout << "\n--- Пункт 12: Карта Карно ---" << std::endl;
        NormalForms::printKarnaughMap(all_res, vars);
        break;
    }
    }
}