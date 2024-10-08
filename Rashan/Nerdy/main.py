#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    /**
    * declare variable couponColor as int
    */
    int couponColor;
    
    /**
    * declare variable haircutType as char 
    */
    char haircutType;
    
    /**
    * declare constant variables ADULT and KIDS
    * and assign the value 
    */
    const float ADULT = 15.50;
    const float KIDS = 10.50;
    
    /**
    * declare variable charge as float
    */
    float charge;
    
    /**
    * getting couponColor from the user
    */
    cout << "Enter coupon color (0 = no coupon, 1 = green, 2 = blue): ";
    cin >> couponColor;
    
    /**
    * getting haircutType from the user
    */
    cout << "Enter the type of haircut (a = adult or k = kid): ";
    cin >> haircutType;

    /**
    * checking couponColor is equal to 1 and haircutType is equal to 'a'
    * then calculate charge as ADULT - 3.50
    */
    if((couponColor == 1) && (haircutType == 'a'))
    {
        charge = ADULT - 3.50;
    }
    /**
    * checking couponColor is equal to 1 and haircutType is equal to 'k'
    * then calculate charge as KIDS - 2.50
    */
    else if((couponColor == 1) && (haircutType == 'k'))
    {
        charge = KIDS - 2.50;
    }
    /**
    * checking couponColor is equal to 2 and haircutType is equal to 'a'
    * then calculate charge as ADULT - 2.50
    */
    else if((couponColor == 2) && (haircutType == 'a'))
    {
        charge = ADULT - 2.50;
    }
    /**
    * checking couponColor is equal to 2 and haircutType is equal to 'k'
    * then calculate charge as KIDS - 1.50
    */
    else if((couponColor == 2) && (haircutType == 'k'))
    {
        charge = KIDS - 1.50;
    }
    /**
    * checking couponColor is equal to 0 and haircutType is equal to 'a'
    * then calculate charge as ADULT
    */
    else if((couponColor == 0) && (haircutType == 'a'))
    {
        charge = ADULT;
    }
    /**
    * checking couponColor is equal to 0 and haircutType is equal to 'k'
    * then calculate charge as KIDS
    */
    else if((couponColor == 0) && (haircutType == 'k'))
    {
        charge = KIDS;
    }
    
    /**
    * display the charge on the console
    */
    cout << "The charge is " << setprecision(2) << fixed << charge << endl;

    return 0;
}
