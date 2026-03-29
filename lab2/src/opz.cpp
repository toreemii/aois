#include "../include/opz.h"
#include "../include/exceptions.h"
#include <stack>

int OPZ::getPriority(char op)
{
    if (op == '!')
        return 4;
    if (op == '&')
        return 3;
    if (op == '|')
        return 2;
    if (op == '>' || op == '~')
        return 1;
    return 0;
}

std::string OPZ::toPostfix(const std::string &infix)
{
    std::string postfix = "";
    std::stack<char> s;

    for (char c : infix)
    {
        if (c >= 'a' && c <= 'e')
        {
            postfix += c;
        }
        else if (c == '(')
        {
            s.push(c);
        }
        else if (c == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                postfix += s.top();
                s.pop();
            }
            if (s.empty())
                throw BracketError();
            s.pop();
        }
        else
        {
            while (!s.empty() && getPriority(s.top()) >= getPriority(c))
            {
                if (c == '!' && s.top() == '!')
                    break;
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty())
    {
        if (s.top() == '(')
            throw BracketError();
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

bool OPZ::evaluate(const std::string &postfix, std::map<char, bool> &values)
{
    std::stack<bool> s;
    for (char c : postfix)
    {
        if (c >= 'a' && c <= 'e')
        {
            s.push(values[c]);
        }
        else if (c == '!')
        {
            if (s.empty())
                return false;
            bool v = s.top();
            s.pop();
            s.push(!v);
        }
        else
        {
            if (s.size() < 2)
                return false;
            bool v2 = s.top();
            s.pop();
            bool v1 = s.top();
            s.pop();
            if (c == '&')
                s.push(v1 && v2);
            else if (c == '|')
                s.push(v1 || v2);
            else if (c == '>')
                s.push(!v1 || v2);
            else if (c == '~')
                s.push(v1 == v2);
        }
    }
    return s.empty() ? false : s.top();
}