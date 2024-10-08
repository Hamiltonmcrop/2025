/**
 *Salon Haircut
 * CSE 100
 *
 * */

#include<iostream>
#include<iomanip>
using namespace std;

/**
 * Function to calculate the total cost based on discounts and service type
 */
float calculateCost(int discountCode, char serviceType) {
    const float ADULT_COST = 18.00;  // Cost for adult service
    const float CHILD_COST = 12.00;  // Cost for child service
    float totalCost;

    /**
     * If green discount and adult service, reduce price by 4.00
     */
    if(discountCode == 1 && serviceType == 'x') {
        totalCost = ADULT_COST - 4.00;
    }
    /**
     * If green discount and child service, reduce price by 2.00
     */
    else if(discountCode == 1 && serviceType == 'y') {
        totalCost = CHILD_COST - 2.00;
    }
    /*'
     * If blue discount and adult service, reduce price by 3.00
     */
    else if(discountCode == 2 && serviceType == 'x') {
        totalCost = ADULT_COST - 3.00;
    }
    /*
     * If blue discount and child service, reduce price by 1.50
     */
    else if(discountCode == 2 && serviceType == 'y') {
        totalCost = CHILD_COST - 1.50;
    }
    /**
     * If no discount, full price for adult service
     */
    else if(discountCode == 0 && serviceType == 'x') {
        totalCost = ADULT_COST;
    }
    /**
     * If no discount, full price for child service
     */
    else if(discountCode == 0 && serviceType == 'y') {
        totalCost = CHILD_COST;
    }
    return totalCost;
}

int main() {
    /**
     * Variable for storing discount code
     * 0 = No discount, 1 = Green, 2 = Blue
     */
    int promoCode;

    /**
     * Variable for storing service type (x = adult, y = child)
     */
    char serviceClass;
    
    /**
     * Get the discount code from the user
     */
    cout << "Enter coupon color (0 for none, 1 for green, 2 for blue):\n ";
    cin >> promoCode;
    
    /**
     * Get the type of service the user wants
     */
    cout << "Enter Haircut type (x for adult, y for child):\n ";
    cin >> serviceClass;

    /**
     * Call the function to compute the total cost
     */
    float totalPrice = calculateCost(promoCode, serviceClass);
    /**
     * Display the final price to the user
     */
    cout << "The total price for the service is:\n";
    cout << "_ _ _ _ _" << endl;
    cout << "$" << fixed << setprecision(2) << totalPrice << endl;
    cout << "- - - - - " << endl;
    return 0;
}
