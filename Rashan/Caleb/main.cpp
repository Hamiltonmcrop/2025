/**
 * Paycheck Calculation Program
 * This program calculates a paycheck based on hours worked, pay rate per hour, 
 * and an optional bonus. If the bonus is not provided, it defaults to zero.
 * 
 * Author: Abel [Panther ID]
 */

#include <iostream>
#include <string>
using namespace std;

int main()
{
    // Declare variables for hours worked, pay rate, and bonus (default to 0)
    int hoursWorked, payRate, bonus = 0;
    int paycheck;            // Variable to store the calculated paycheck
    string bonusInput;       // Temporary string to read optional bonus input

    // Prompt the user to enter hours worked
    cout << "Enter hours worked: ";
    cin >> hoursWorked;

    // Prompt the user to enter pay rate per hour
    cout << "Enter pay rate per hour: ";
    cin >> payRate;

    // Prompt for bonus (optional input)
    cout << "Enter bonus (optional, press Enter if none): ";
    cin.ignore();            // Clear the newline left in the input buffer from previous input
    getline(cin, bonusInput); // Get the entire line for bonus input (allows it to be empty)

    // Check if the bonus input is not empty; if it has a value, convert it to an integer
    if (!bonusInput.empty()) {
        bonus = stoi(bonusInput); // Convert bonus input from string to integer
    }

    // Calculate the total paycheck using hours worked, pay rate, and optional bonus
    paycheck = (hoursWorked * payRate) + bonus;

    // Output the calculated paycheck amount
    cout << "Your paycheck is: $" << paycheck << endl;

    return 0; // Indicate successful program termination
}

