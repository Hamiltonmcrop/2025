// Abel [Panther ID]
// Paycheck Calculation Program

#include <iostream>
using namespace std;

int main()
{
    int hoursWorked, payRate, bonus = 0;
    int paycheck;

    // Input hours worked and pay rate
    cout << "Enter hours worked: ";
    cin >> hoursWorked;

    cout << "Enter pay rate per hour: ";
    cin >> payRate;

    // Optional input for bonus
    cout << "Enter bonus (optional, press Enter if none): ";
    if (cin.peek() != '\n') cin >> bonus;

    // Calculate paycheck
    paycheck = (hoursWorked * payRate) + bonus;

    // Output paycheck amount
    cout << "Your paycheck is: " << paycheck << endl;

    return 0;
}
