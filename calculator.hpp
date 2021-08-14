#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

class Calculator {
    friend ostream& operator<<(ostream& out, const Calculator& calculator);
    friend void operator<<(Calculator& calculator, const string& str);

private:
    queue<string> postfix;
    stack<int> instructions;
    unordered_map<char, int> precedence = { {'+', 1}, {'-', 1}, {'x', 2}, {'*', 2}, {'/', 2}, {'^', 3}, {'s', 3} };

public:
    string toString(const char& ch);
    void getPostfixNotation(const string& infix);
    void evaluate();
    int getAnswer() const;
};

#endif
