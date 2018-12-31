#include <iostream>
#include <string>
#include <vector>
#include "Stack.hpp"

using ds::Stack;
using std::cin;
using std::cout;
using std::string;
using std::vector;

vector<string> toPostfix(vector<string> expr);
bool isOperator(string ele);
bool isOperand(string ele);
bool isOpenParen(string ele);
bool isCloseParen(string ele);
int getPriority(string op);
bool hasPriority(string op1, string op2);

int main()
{
    vector<string> expression;
    string element;
    while (cin >> element && !cin.eof()) {
        expression.push_back(element);
    }

    expression = toPostfix(expression);

    cout << expression[0];
    for (size_t i = 1; i < expression.size(); i++) {
        cout << " " << expression[i];
    }
    cout << std::endl;

    return 0;
}

vector<string> toPostfix(vector<string> expr)
{
    Stack<string> ele_stack;
    vector<string> postfix_expr;
    for (size_t i = 0; i < expr.size(); i++) {
        // if element is an operand, just append it
        if (isOperand(expr[i])) {
            postfix_expr.push_back(expr[i]);
        }
        // If element is operator, compare priority with stack top until the first opening bracket, and pop them
        // then push the current operator
        else if (isOperator(expr[i])) {
            while (!ele_stack.empty() && !isOpenParen(ele_stack.top()) && hasPriority(ele_stack.top(), expr[i])) {
                postfix_expr.push_back(ele_stack.top());
                ele_stack.pop();
            }
            ele_stack.push(expr[i]);
        }
        // if opening bracket, push it
        else if (isOpenParen(expr[i])) {
            ele_stack.push(expr[i]);
        }
        // if closing bracket, pop all operators unitl "(", and pop the "("
        else if (isCloseParen(expr[i])) {
            while (!ele_stack.empty() && !isOpenParen(ele_stack.top())) {
                postfix_expr.push_back(ele_stack.top());
                ele_stack.pop();
            }
            ele_stack.pop();
        }
    }
    // finally pop all elements in stack
    while (!ele_stack.empty()) {
        postfix_expr.push_back(ele_stack.top());
        ele_stack.pop();
    }

    return postfix_expr;
}

bool isOperator(string ele)
{
    if (ele.size() != 1) {
        return false;
    }
    return (ele == "+" || ele == "-" || ele == "*" || ele == "/");
}

bool isOperand(string ele)
{
    return (!isOperator(ele) && !isOpenParen(ele) && !isCloseParen(ele));
}

bool isOpenParen(string ele)
{
    if (ele.size() != 1) {
        return false;
    }
    return (ele == "(");
}

bool isCloseParen(string ele)
{
    if (ele.size() != 1) {
        return false;
    }
    return (ele == ")");
}

int getPriority(string op)
{
    switch (op[0]) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

bool hasPriority(string op1, string op2)
{
    return (getPriority(op1) >= getPriority(op2));
}