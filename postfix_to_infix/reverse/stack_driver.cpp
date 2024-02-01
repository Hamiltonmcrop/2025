// stack_driver.cpp

#include "stack.h"

int main() {
    string infix = "";
    string answer = "y";
    stack s;

    do {
        cout << "Please enter an infix expression: " << endl;
        getline(cin, infix);
        s.infixToPostfix(infix);
        cout << "Enter another expression? (y/n): ";
        cin >> answer;
        cin.ignore();
    } while (answer == "y" || answer == "Y");

    return 0;
}

