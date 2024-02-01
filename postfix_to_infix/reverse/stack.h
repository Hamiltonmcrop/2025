// stack.h

#pragma once

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <string>
#include <string.h>
using namespace std;

class node {
public:
    string expression;
    node* next = 0;
};

class stack {
public:
    stack();
    ~stack();
    void infixToPostfix(const string& infix);
    string first();
    void pop();
    void push(const string& s);
    void print();
    bool isEmpty() const { return top == nullptr; }
private:
    node* top;
    bool hasHigherOrEqualPrecedence(const string& op1, char op2);
    int getOperatorPrecedence(char op);
};

#endif // STACK_H

