// stack.cpp

#include "stack.h"

stack::stack() {
    top = nullptr;
}

stack::~stack() {
    while (top != nullptr) {
        pop();
    }
}

void stack::infixToPostfix(const string& infix) {
    string postfix;
    stack operators;

    for (int i = 0; i < int(infix.length()); i++) {
        char currentChar = infix[i];

        if (isalpha(currentChar)) {
            postfix += currentChar;
        } else if (currentChar == '(') {
            operators.push("(");
        } else if (currentChar == ')') {
            while (!operators.isEmpty() && operators.top != nullptr && operators.top->expression != "(") {
                postfix += " " + operators.top->expression;
                operators.pop();
            }
            operators.pop();
        } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            while (!operators.isEmpty() && operators.top != nullptr && operators.top->expression != "(" &&
                   hasHigherOrEqualPrecedence(operators.top->expression, currentChar)) {
                postfix += " " + operators.top->expression;
                operators.pop();
            }
            operators.push(string(1, currentChar));
        }
    }

    while (!operators.isEmpty()) {
        postfix += " " + operators.top->expression;
        operators.pop();
    }

    cout << postfix << endl;
}

string stack::first() {
    if (top == nullptr) {
        cout << "no expressions in stack" << endl;
        exit(-1);
    }
    return top->expression;
}

void stack::pop() {
    if (top == nullptr) {
        cout << "too many operators" << endl;
        return;
    }
    node* temp;
    if (top != nullptr) {
        temp = top;
        top = top->next;
        delete temp;
    }
}

void stack::push(const string& s) {
    node* temp = new node;
    temp->expression = s;
    temp->next = top;
    top = temp;
}

void stack::print() {
    if (top->next != nullptr) {
        cout << "too many operands" << endl;
        return;
    }
    cout << top->expression << endl;
}

bool stack::hasHigherOrEqualPrecedence(const string& op1, char op2) {
    int precedenceOp1 = getOperatorPrecedence(op1[0]);
    int precedenceOp2 = getOperatorPrecedence(op2);

    return (precedenceOp1 >= precedenceOp2);
}

int stack::getOperatorPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

