#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <unordered_map>
#include "./lib/LinkedLib/LinkedQueue.hpp"
#include "./lib/LinkedLib/LinkedStack.hpp"

class Calculator {
    friend std::ostream& operator<<(std::ostream& out, const Calculator& calculator);
    friend void operator<<(Calculator& calculator, const std::string& str);

private:
    LinkedQueue<std::string> postfix;
    LinkedStack<int> instructions;
    std::unordered_map<char, int> precedence = { {'+', 1}, {'-', 1}, {'x', 2}, {'*', 2}, {'/', 2}, {'^', 3}, {'s', 3} };

public:
    std::string toString(const char& ch);
    void getPostfixNotation(const std::string& infix);
    void evaluate();
    int getAnswer() const;
};

#endif
