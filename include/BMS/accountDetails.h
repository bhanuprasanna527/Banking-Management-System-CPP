//
// Created by Bhanu Prasanna on 31/12/23.
//

#ifndef BMS_ACCOUNTDETAILS_H
#define BMS_ACCOUNTDETAILS_H

#include <iostream>
#include <pqxx/pqxx>
using namespace std;

bool fetchCustomerDetails (int customerID) {
    try {
        pqxx::connection customer("dbname=BMS");
        pqxx::transaction custTX(customer);

        for (auto [customerid, lastName, firstName, dateofbirth, emailid, phonenumber, taxid, customeraddress, customerpassword] : custTX.query<int, string, string, string, string, string, string, string, string>(
                "SELECT * FROM customer;"
                )) {
            if (customerID == customerid) {
                string pCheck;
                system("clear");
                cout << "\n\n" << string(15, ' ') << "We must check you by verifying password.\n\n";
                cout << string(18, ' ') << "Enter password: ";
                cin >> pCheck;
                if (pCheck == customerpassword) {
                    system("clear");
                    cout << string(80, '=') << endl;
                    cout << string(30, ' ') << "Account Details"<< endl;
                    cout << string(80, '=') << "\n\n\n";

                    cout << string(18, ' ') << "Customer ID: " << customerid << endl;
                    cout << string(18, ' ') << "Last Name: " << lastName << endl;
                    cout << string(18, ' ') << "First Name: " << firstName << endl;
                    cout << string(18, ' ') << "Date of Birth: " << dateofbirth << endl;
                    cout << string(18, ' ') << "Email ID: " << emailid << endl;
                    cout << string(18, ' ') << "Phone Number: " << phonenumber << endl;
                    cout << string(18, ' ') << "Customer Address: " << customeraddress << endl;

                    int goBack;
                    cout << "\n\n" << string(3, ' ') << "Press 0 to exit or any number to go to Menu: ";
                    cin >> goBack;
                    if (goBack == 0) {
                        exit(0);
                    } else {
                        return true;
                    }
                }
            }
        }
    } catch (std::exception const &e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }

    return false;
}

#endif //BMS_ACCOUNTDETAILS_H
