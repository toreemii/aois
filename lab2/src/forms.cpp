#include "../include/forms.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <set>

std::string NormalForms::getSDNF(const std::vector<char> &vars, const std::vector<std::map<char, bool>> &ones)
{
    if (ones.empty())
        return "0 (Константа 0)";
    std::string res = "";
    for (size_t i = 0; i < ones.size(); i++)
    {
        res += "(";
        for (size_t j = 0; j < vars.size(); j++)
        {
            if (!ones[i].at(vars[j]))
                res += "!";
            res += vars[j];
            if (j < vars.size() - 1)
                res += "&";
        }
        res += ")";
        if (i < ones.size() - 1)
            res += " | ";
    }
    return res;
}

std::string NormalForms::getSKNF(const std::vector<char> &vars, const std::vector<std::map<char, bool>> &zeros)
{
    if (zeros.empty())
        return "1 (Константа 1)";
    std::string res = "";
    for (size_t i = 0; i < zeros.size(); i++)
    {
        res += "(";
        for (size_t j = 0; j < vars.size(); j++)
        {
            if (zeros[i].at(vars[j]))
                res += "!";
            res += vars[j];
            if (j < vars.size() - 1)
                res += "|";
        }
        res += ")";
        if (i < zeros.size() - 1)
            res += " & ";
    }
    return res;
}

std::string NormalForms::getNumericSDNF(const std::vector<int> &indices)
{
    std::string res = "f_сднф = Sum(";
    for (size_t i = 0; i < indices.size(); i++)
    {
        res += std::to_string(indices[i]) + (i == indices.size() - 1 ? "" : ", ");
    }
    return res + ")";
}

std::string NormalForms::getNumericSKNF(const std::vector<int> &indices)
{
    std::string res = "f_скнф = Mult(";
    for (size_t i = 0; i < indices.size(); i++)
    {
        res += std::to_string(indices[i]) + (i == indices.size() - 1 ? "" : ", ");
    }
    return res + ")";
}

std::string NormalForms::getFunctionIndex(const std::vector<bool> &results)
{
    long long index = 0;
    int n = results.size();
    for (int i = 0; i < n; i++)
    {
        if (results[i])
            index += std::pow(2, n - 1 - i);
    }
    return "Индекс функции: " + std::to_string(index);
}

PostClasses NormalForms::checkPostClasses(const std::vector<bool> &res, int varCount)
{
    PostClasses p;
    int n = res.size();
    p.t0 = (res[0] == 0);
    p.t1 = (res[n - 1] == 1);

    p.s = true;
    for (int i = 0; i < n / 2; i++)
        if (res[i] == res[n - 1 - i])
            p.s = false;

    p.m = true;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i & j) == i && res[i] > res[j])
                p.m = false;
        }
    }

    p.l = true;
    std::vector<bool> c = res;
    for (int i = 1; i < n; i++)
    {
        for (int j = n - 1; j >= i; j--)
            c[j] = c[j] ^ c[j - 1];
    }
    for (int i = 0; i < n; i++)
    {
        if (c[i])
        {
            int bits = 0, t = i;
            while (t)
            {
                bits += (t & 1);
                t >>= 1;
            }
            if (bits > 1)
                p.l = false;
        }
    }
    return p;
}

void NormalForms::printPostTable(const PostClasses &p, const std::vector<bool> &res, int n)
{
    std::cout << "T0: " << (p.t0 ? "+" : "-") << "\n";
    std::cout << "T1: " << (p.t1 ? "+" : "-") << "\n";
    std::cout << "S:  " << (p.s ? "+" : "-") << "\n";
    std::cout << "M:  " << (p.m ? "+" : "-") << "\n";
    std::cout << "L:  " << (p.l ? "+" : "-") << "\n";
}

std::string NormalForms::getZhegalkinPolynomial(const std::vector<bool> &res, const std::vector<char> &vars)
{
    int n = res.size();
    std::vector<bool> c = res, coefs;
    coefs.push_back(c[0]);
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
            c[j] = c[j] ^ c[j + 1];
        coefs.push_back(c[0]);
    }
    std::string poly = "";
    bool first = true;
    for (int i = 0; i < n; i++)
    {
        if (coefs[i])
        {
            if (!first)
                poly += " ^ ";
            if (i == 0)
                poly += "1";
            else
            {
                for (int j = 0; j < (int)vars.size(); j++)
                {
                    if ((i >> (vars.size() - 1 - j)) & 1)
                        poly += vars[j];
                }
            }
            first = false;
        }
    }
    return poly.empty() ? "0" : poly;
}

void NormalForms::findVariablesType(const std::vector<bool> &res, const std::vector<char> &vars, std::vector<char> &ess, std::vector<char> &fict)
{
    int n = vars.size();
    for (int i = 0; i < n; i++)
    {
        bool is_ess = false;
        int bit_pos = n - 1 - i;
        for (int j = 0; j < (int)res.size(); j++)
        {
            if (!((j >> bit_pos) & 1))
            {
                if (res[j] != res[j | (1 << bit_pos)])
                {
                    is_ess = true;
                    break;
                }
            }
        }
        if (is_ess)
            ess.push_back(vars[i]);
        else
            fict.push_back(vars[i]);
    }
}

std::vector<bool> NormalForms::getBooleanDerivative(const std::vector<bool> &res, int varIdx, int total)
{
    std::vector<bool> d;
    int pos = total - 1 - varIdx;
    for (int j = 0; j < (int)res.size(); j++)
    {
        d.push_back(res[j & ~(1 << pos)] ^ res[j | (1 << pos)]);
    }
    return d;
}

std::string NormalForms::vectorToTableString(const std::vector<bool> &vec)
{
    std::string s = "[ ";
    for (bool b : vec)
        s += (b ? "1 " : "0 ");
    return s + "]";
}

std::string NormalForms::getMinimizedQuine(const std::vector<char> &vars, const std::vector<int> &ones_i)
{
    int n = vars.size();
    std::set<Implicant> current;
    for (int idx : ones_i)
    {
        Implicant imp;
        for (int i = n - 1; i >= 0; i--)
            imp.bits.push_back((idx >> i) & 1);
        current.insert(imp);
    }
    std::set<Implicant> primes;
    while (!current.empty())
    {
        std::set<Implicant> next;
        std::vector<Implicant> v(current.begin(), current.end());
        std::vector<bool> used(v.size(), false);
        for (size_t i = 0; i < v.size(); i++)
        {
            for (size_t j = i + 1; j < v.size(); j++)
            {
                int diff = 0, pos = -1;
                for (int k = 0; k < n; k++)
                    if (v[i].bits[k] != v[j].bits[k])
                    {
                        diff++;
                        pos = k;
                    }
                if (diff == 1)
                {
                    Implicant m = v[i];
                    m.bits[pos] = -1;
                    next.insert(m);
                    used[i] = used[j] = true;
                }
            }
        }
        for (size_t i = 0; i < v.size(); i++)
            if (!used[i])
                primes.insert(v[i]);
        current = next;
    }
    std::string res = "";
    for (auto &im : primes)
    {
        if (!res.empty())
            res += " v ";
        res += "(";
        for (int i = 0; i < n; i++)
        {
            if (im.bits[i] != -1)
            {
                if (im.bits[i] == 0)
                    res += "!";
                res += vars[i];
            }
        }
        res += ")";
    }
    return res.empty() ? "0" : res;
}

void NormalForms::getQuineMcCluskeyTable(const std::vector<char> &vars, const std::vector<int> &ones_i)
{
    int n = vars.size();

    std::set<Implicant> current;
    for (int idx : ones_i)
    {
        Implicant imp;
        for (int i = n - 1; i >= 0; i--)
            imp.bits.push_back((idx >> i) & 1);
        current.insert(imp);
    }

    std::set<Implicant> primes;
    while (!current.empty())
    {
        std::set<Implicant> next;
        std::vector<Implicant> v(current.begin(), current.end());
        std::vector<bool> used(v.size(), false);
        for (size_t i = 0; i < v.size(); i++)
        {
            for (size_t j = i + 1; j < v.size(); j++)
            {
                int diff = 0, pos = -1;
                for (int k = 0; k < n; k++)
                    if (v[i].bits[k] != v[j].bits[k])
                    {
                        diff++;
                        pos = k;
                    }
                if (diff == 1)
                {
                    Implicant m = v[i];
                    m.bits[pos] = -1;
                    next.insert(m);
                    used[i] = used[j] = true;
                }
            }
        }
        for (size_t i = 0; i < v.size(); i++)
            if (!used[i])
                primes.insert(v[i]);
        current = next;
    }

    std::cout << "\nТаблица покрытия импликантами:\n";
    std::cout << std::setw(10) << "Импл. \\ Набор | ";
    for (int idx : ones_i)
        std::cout << std::setw(3) << idx << " ";
    std::cout << "\n"
              << std::string(15 + ones_i.size() * 4, '-') << "\n";

    for (auto &im : primes)
    {
        std::string s_im = "";
        for (int b : im.bits)
            s_im += (b == -1 ? "-" : std::to_string(b));
        std::cout << std::setw(13) << s_im << " | ";

        for (int idx : ones_i)
        {
            bool covers = true;
            for (int k = 0; k < n; k++)
            {
                int bit_in_idx = (idx >> (n - 1 - k)) & 1;
                if (im.bits[k] != -1 && im.bits[k] != bit_in_idx)
                {
                    covers = false;
                    break;
                }
            }
            std::cout << std::setw(3) << (covers ? "X" : ".") << " ";
        }
        std::cout << "\n";
    }
}

void NormalForms::printKarnaughMap(const std::vector<bool> &results, const std::vector<char> &vars)
{
    int n = vars.size();
    int gray[] = {0, 1, 3, 2};

    if (n == 2)
    { 
        std::cout << "   b\\a | 0 | 1 |\n";
        std::cout << "  -------------\n";
        for (int b = 0; b < 2; b++)
        {
            std::cout << "   " << b << "   | ";
            for (int a = 0; a < 2; a++)
            {
                std::cout << results[(a << 1) | b] << " | ";
            }
            std::cout << "\n";
        }
    }
    else if (n == 3)
    {
        std::cout << " bc\\a | 0 | 1 |\n---------------\n";
        for (int i = 0; i < 4; i++)
        {
            int bc = gray[i];
            std::cout << " " << (bc == 0 ? "00" : bc == 1 ? "01"
                                              : bc == 3   ? "11"
                                                          : "10")
                      << "  | ";
            for (int a = 0; a < 2; a++)
                std::cout << results[(a << 2) | bc] << " | ";
            std::cout << "\n";
        }
    }
    else if (n == 4)
    {
        std::cout << " cd\\ab| 00| 01| 11| 10|\n-----------------------\n";
        for (int i = 0; i < 4; i++)
        {
            int cd = gray[i];
            std::cout << " " << (cd == 0 ? "00" : cd == 1 ? "01"
                                              : cd == 3   ? "11"
                                                          : "10")
                      << " | ";
            for (int j = 0; j < 4; j++)
                std::cout << " " << results[(gray[j] << 2) | cd] << " |";
            std::cout << "\n";
        }
    }
    else
    {
        std::cout << "Карта Карно доступна для 3 или 4 переменных.\n";
    }
}