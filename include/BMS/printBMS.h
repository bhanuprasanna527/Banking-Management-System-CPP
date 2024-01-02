//
// Created by Bhanu Prasanna on 30/12/23.
//

#ifndef BMS_PRINTBMS_H
#define BMS_PRINTBMS_H

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

void printSystem (string errorMessage = "Please enter between (1-10).") {
    system("clear");

    cout << string(80, '=') << endl;
    cout << string(28, ' ') << "Banking Management System"<< endl;
    cout << string(80, '=') << "\n\n";

    cout << string(6, ' ') << "MAIN MENU:" << "\n\n";
    cout << string(12, ' ') << "1. Account Details" << endl;
    cout << string(12, ' ') << "2. New Customer" << endl;
    cout << string(12, ' ') << "3. New Account" << endl;
    cout << string(12, ' ') << "4. Deposit Amount" << endl;
    cout << string(12, ' ') << "5. Withdraw Amount" << endl;
    cout << string(12, ' ') << "6. Close Account" << endl;
    cout << string(12, ' ') << "7. Edit Account Details" << endl;
    cout << string(12, ' ') << "8. View Transaction History" << endl;
    cout << string(12, ' ') << "9. PDF Statement" << endl;
    cout << string(12, ' ') << "10. Know your CustomerID" << endl;
    cout << string(12, ' ') << "11. Know your Account Details" << endl;
    cout << string(12, ' ') << "12. Exit" << endl;

    cout << "\n";

    cout << string(9, ' ') << errorMessage << "\n\n";
    cout << string(15, ' ') << "Enter your purpose of Visit: ";
}

#endif //BMS_PRINTBMS_H
