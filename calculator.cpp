#include "calculator.hpp"

std::ostream& operator<<(std::ostream& out, Calculator& calculator) {
    out << calculator.getAnswer();
    return out;
}

void operator<<(Calculator& calculator, const std::string& infix) {
    calculator.getPostfixNotation(infix);
}

std::string Calculator::toString(const char& ch) {
    std::string temp = "";
    temp += ch;
    return temp;
}

std::string Calculator::trimTrailingZeros(std::string str) {
    if (str.find('.') != std::string::npos)
    {
        str = str.substr(0, str.find_last_not_of('0') + 1);
        if (str.find('.') == str.size() - 1)
            str = str.substr(0, str.size() - 1);
    }
    return str;
}

void Calculator::AC() {
    postfix.empty();
    instructions.empty();
}

void Calculator::getPostfixNotation(const std::string& infix) {
    int i = 0;
    LinkedStack<char> infixOperators;
    while (i < infix.size()) {
        char ch = infix[i];

        if (std::isdigit(ch) || ch == '.') {
            std::string temp = toString(ch);
            while (i + 1 < infix.size() && (isdigit(infix[i + 1]) || infix[i + 1] == '.'))
                temp += infix[++i];

            postfix.push(temp);
            ch = infix[i];
        }
        else if (ch == '(')
            infixOperators.push('(');
        else if (ch == ')') {
            while (infixOperators.top() != '(') {
                postfix.push(toString(infixOperators.top()));
                infixOperators.pop();
            }
            infixOperators.pop();
        }
        else if (ch != ' ') {
            while (!infixOperators.empty() && precedence[ch] <= precedence[infixOperators.top()]) {
                postfix.push(toString(infixOperators.top()));
                infixOperators.pop();
            }
            infixOperators.push(ch);
        }
        i++;
    }

    while (!infixOperators.empty()) {
        postfix.push(toString(infixOperators.top()));
        infixOperators.pop();
    }
}

void Calculator::evaluate() {
    while (!postfix.empty()) {
        std::string str = postfix.top();
        if (!std::isdigit(str[0])) {
            double n1 = instructions.top();
            instructions.pop();
            double n2 = instructions.top();
            instructions.pop();

            if (str[0] == '+')
                instructions.push(n2 + n1);
            else if (str[0] == '-')
                instructions.push(n2 - n1);
            else if (str[0] == 'x' || str[1] == '*')
                instructions.push(n2 * n1);
            else if (str[0] == '/')
                instructions.push(n2 / n1);
            else if (str[0] == '^')
                instructions.push(pow(n2, n1));
            else if (str[0] == 'r')
                instructions.push(pow(n1, 1.0 / n2));
        }
        else {
            instructions.push(std::stod(trimTrailingZeros(str)));
        }

        postfix.pop();
    }
}

std::string Calculator::getAnswer() {
    return trimTrailingZeros(std::to_string(instructions.top()));
}
