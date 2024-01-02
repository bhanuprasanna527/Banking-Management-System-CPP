#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "printBMS.h"
#include "accountCreation.h"
#include "accountDetails.h"
#include "getCustomerID.h"
using namespace std;

void systemBMS () {
    int job;

    do {
        printSystem();
        cin >> job;
        switch (job) {
            case 1: {
                int customerID;
                cout << string(15, ' ') << "Enter your CustomerID: ";
                cin >> customerID;
                if (!fetchCustomerDetails(customerID)) {
                    cout << "\n\n\n" << string(21, ' ') << "No account was found with CustomerID: " << customerID << endl;
                    sleep(5);
                }
                break;
            }
            case 2: {
                createCustomer();
                break;
            }
            case 3: {
                string TaxID;
                cout << string(12, ' ') << "\nTax Identification Number: ";
                cin >> TaxID;
                createAccount(TaxID);
                break;
            }
            case 10: {
                system("clear");
                fetchCustomerID();
                break;
            }
            case 11: {
                int customerID;
                cout << string(15, ' ') << "Enter your CustomerID: ";
                cin >> customerID;
                if (!fetchAccountDetails(customerID)) {
                    cout << "\n\n\n" << string(21, ' ') << "No account was found with CustomerID: " << customerID << endl;
                    sleep(5);
                }
                break;
            }
            case 12: {
                exit(0);
            }
            default: {
                printSystem();
            }
        }
    } while (job != 9);
}