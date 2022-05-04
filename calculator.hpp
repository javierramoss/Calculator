#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <unordered_map>
#include "./lib/LinkedLib/linkedqueue.hpp"
#include "./lib/LinkedLib/linkedstack.hpp"

class Calculator {
    friend std::ostream& operator<<(std::ostream& out, Calculator& calculator);
    friend void operator<<(Calculator& calculator, const std::string& str);

private:
    LinkedQueue<std::string> postfix;
    LinkedStack<double> instructions;
    std::unordered_map<char, int> precedence = { {'+', 1}, {'-', 1}, {'x', 2}, {'*', 2}, {'/', 2}, {'^', 3}, {'s', 3} };

public:
    std::string toString(const char& ch);
    std::string trimTrailingZeros(std::string str);
    void AC();
    void getPostfixNotation(const std::string& infix);
    void evaluate();
    std::string getAnswer();
};

#endif
