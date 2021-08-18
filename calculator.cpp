#include "calculator.hpp"

ostream& operator<<(ostream& out, const Calculator& calculator) {
    out << calculator.getAnswer();
    return out;
}

void operator<<(Calculator& calculator, const string& infix) {
    calculator.getPostfixNotation(infix);
}

string Calculator::toString(const char& ch) {
    string temp = "";
    temp += ch;
    return temp;
}

void Calculator::getPostfixNotation(const string& infix) {
    int i = 0;
    stack<char> infixOperators;
    while (i < infix.size()) {
        char ch = infix[i];

        if (std::isdigit(ch)) {
            string temp = toString(ch);
            while (i + 1 < infix.size() && isdigit(infix[i + 1]))
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
        string str = postfix.top();
        if (!std::isdigit(str[0])) {
            int n1 = instructions.top();
            instructions.pop();
            int n2 = instructions.top();
            instructions.pop();

            if (str[0] == '+')
                instructions.push(n2 + n1);
            else if (str[0] == '-')
                instructions.push(n2 - n1);
            else if (str[0] == 'x' || str[0] == '*')
                instructions.push(n2 * n1);
            else if (str[0] == '/')
                instructions.push(n2 / n1);
            else if (str[0] == '^')
                instructions.push(pow(n2, n1));
            else if (str[0] == 's')
                instructions.push(pow(n1, 1.0 / n2));
        }
        else {
            instructions.push(stoi(str));
        }

        postfix.pop();
    }
}

int Calculator::getAnswer() const {
    return instructions.top();
}
