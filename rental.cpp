//
//  rental.cpp
//  Week2
//
//  Created by Margaret Capetz on 10/6/21.

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, const char * argv[]) {
    
    //declare variables
    int baseCharge = 43;
    int luxBaseCharge = 71;
    int ostart, oend, days, month;
    string customer;
    string luxCar;
    double charge;
    
    //obtain user input
    cout << "Odometer at start: ";
    cin >> ostart;
  
    cout << "Odometer at end: ";
    cin >> oend;
   
    cout << "Rental days: ";
    cin >> days;
    cin.ignore(10000, '\n');
    
    cout << "Customer name: ";
    getline(cin, customer);
    
    cout << "Luxury car? (y/n): ";
    getline(cin, luxCar);
    
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    cin >> month;
    
    cout << "---" << endl;
    
    //throw errors
    if(ostart < 0) {
        cout << "The starting odometer reading must not be negative." << endl;
        return 1; // non-zero return value means program couldn't do its job
    }
    else if(oend < ostart) {
        cout << "The ending odometer reading must be at least as large as the starting reading." << endl;
        return 1;
    }
    else if(days <= 0) {
        cout << "The number of rental days must be positive." << endl;
        return 1;
    }
    else if(customer == "") {
        cout << "You must enter a customer name." << endl;
        return 1;
    }
    else if(luxCar != "y" && luxCar != "n") {
        cout << "You must enter y or n." << endl;
        return 1;
    }
    else if(month < 1 || month > 12) {
        cout << "The month number must be in the range 1 through 12." << endl;
        return 1;
    }
    
    //no errors in input, so the rental charge will be calculated
    
    //calculate distance
    int distance = oend - ostart;
    
    //calculate price based on distance
    if(month < 4 || month > 11){
        //winter
        if(distance <= 500) charge = distance * 0.27;
        else charge = (500 * 0.27) + (distance - 500)*0.17;
    }
    else{
        //not winter
        if(distance <= 100) charge = distance * 0.27;
        else if(distance <= 500) charge = (100*0.27) + (distance - 100)*0.21;
        else charge = (100 * 0.27) + (400 * 0.21) + (distance - 500)*0.17;
    }
    
    //calculate price based on rental days & whether or not the car is luxury
    if(luxCar == "y"){
        charge += days * luxBaseCharge;
    }
    else charge += days * baseCharge;
    
    //print final amount with customer name
    cout << "The rental charge for " << customer << " is $";
    cout << std::setprecision(2) << std::fixed; //print 2 decimal places for the amount
    cout << charge << endl;
    return 0;
    

}
