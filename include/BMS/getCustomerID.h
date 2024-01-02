//
// Created by Bhanu Prasanna on 31/12/23.
//

#ifndef BMS_GETCUSTOMERID_H
#define BMS_GETCUSTOMERID_H

#include <pqxx/pqxx>
#include <iostream>
#include <string>
using namespace std;

void fetchCustomerID () {
    try {

        cout << string(80, '=') << endl;
        cout << string(30, ' ') << "Get CustomerID"<< endl;
        cout << string(80, '=') << "\n\n\n";

        string TaxID;

        cout << "\n\n" << string(15, ' ') << "We must check you by verifying TaxID.\n\n";
        cout << string(18, ' ') << "Enter TaxID: ";
        cin >> TaxID;

        pqxx::connection customer("dbname=BMS");

        string qu = "SELECT customerid FROM customer WHERE taxid = '" + TaxID + "';";

        pqxx::nontransaction custNTX(customer);

        pqxx::result R(custNTX.exec(qu));

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << "\n\n" << string(15, ' ') << "This is your CustomerID: " << c[0].as<int>() << endl;
            cout << "\n\n" << string(12, ' ') << "Please Note it Down as it will only be shown for 10 seconds!" << endl;
            sleep(10);
        }
        system("clear");

        cout << "\n\n" << "If your CustomerID is not visible that means you are not a customer of our bank!" << endl;
        cout << "Please create an Account with us and fill the necessary information!" << endl;
        cout << "\n\n" << string(24, ' ') << "Thank you for choosing BMS!\n\n" << endl;

        int goBack;
        cout << "Press 0 to exit or any number to go to Menu: ";
        cin >> goBack;
        if (goBack == 0) {
            exit(0);
        }

    } catch (std::exception const &e)
    {

        std::cerr << "ERROR: " << e.what() << '\n';

    }
}

#endif //BMS_GETCUSTOMERID_H
