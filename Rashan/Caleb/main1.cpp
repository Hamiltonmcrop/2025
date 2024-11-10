/**
 *Payckeck Calculation Program
 */

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int hoursWorked, payRate, bonus = 0;
    int paycheck;
    string bonusInput;

    // Input hours worked and pay rate
    cout << "Enter hours worked: ";
    cin >> hoursWorked;

    cout << "Enter pay rate per hour: ";
    cin >> payRate;

    // Prompt for bonus
    cout << "Enter bonus (optional, press Enter if none): ";
    cin.ignore();  // Ignore any leftover newline character in the input buffer
    getline(cin, bonusInput);

    // If bonus input is not empty, convert it to an integer
    if (!bonusInput.empty()) {
        bonus = stoi(bonusInput);
    }

    // Calculate paycheck
    paycheck = (hoursWorked * payRate) + bonus;

    // Output paycheck amount
    cout << "Your paycheck is: $" << paycheck << endl;

    return 0;
}
