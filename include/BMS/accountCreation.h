//
// Created by Bhanu Prasanna on 30/12/23.
//

#ifndef BMS_ACCOUNTCREATION_H
#define BMS_ACCOUNTCREATION_H

#include <iostream>
#include <string>
#include <pqxx/pqxx>
using namespace std;

void goBackFun() {
    int goBack;
    cout << "Press 0 to exit or any number to go to Menu: ";
    cin >> goBack;
    if (goBack == 0) {
        exit(0);
    }
}

bool checkTaxID (const string& TaxID) {
    try {
        pqxx::connection customer("dbname=BMS");

        pqxx::work custTX(customer);

        for (auto [taxid] : custTX.query<string>(
                "SELECT taxid FROM customer;"
                )) {
            if (TaxID == taxid) {
                return true;
            }
        }
    } catch (std::exception const &e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }

    return false;
}

bool checkCustomerID (int customerID) {
    try {
        pqxx::connection account("dbname=BMS");

        pqxx::work accTX(account);

        for (auto [customerid] : accTX.query<int>(
                "SELECT customerid FROM account WHERE customerid = " + to_string(customerID) + ";"
        )) {
            if (customerID == customerid) {
                return true;
            }
        }
    } catch (std::exception const &e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }

    return false;
}

void createCustomer () {
    string TaxID, lastName, firstName, dateOfBirth, emailID, phoneNumber, customerAddress, customerPassword;
    cout << string(12, ' ') << "\nTax Identification Number: ";
    cin >> TaxID;

    if (checkTaxID(TaxID)) {
        system("clear");

        cout << "\n\n\n" << string(15, ' ') << "You are already our customer!" << endl;
        cout << string(21, ' ') << "Thank you\n\n";

        int goBack;
        cout << "Press 0 to exit or any number to go to Menu: ";
        cin >> goBack;
        if (goBack == 0) {
            exit(0);
        }
    } else {
        system("clear");
        cout << "You are not a Customer!\nThat's Great let us open an profile in our BMS for you!" << endl;

        cout << string(6, ' ') << "We need the following information to go forward:\n\n";

        cout << string(9, ' ') << "Last Name: ";
        cin >> lastName;
        cout << string(9, ' ') << "First Name: ";
        cin >> firstName;
        cout << string(9, ' ') << "Date of Birth (Format: YYYY-MM-DD): ";
        cin >> dateOfBirth;
        cout << string(9, ' ') << "Email ID: ";
        cin >> emailID;
        cout << string(9, ' ') << "Phone Number: ";
        cin >> phoneNumber;
        cout << string(9, ' ') << "Customer Address: ";
        cin >> customerAddress;
        cout << string(9, ' ') << "Customer Password: ";
        cin >> customerPassword;

        try {
            pqxx::connection customer("dbname=BMS");
            pqxx::work custTX(customer);

            string qu = "INSERT INTO customer (lastname, firstname, dateofbirth, emailid, "
                        "phonenumber, taxid, customeraddress, customerpassword) VALUES ('" + lastName + "', '"
                        + firstName + "', '" + dateOfBirth + "', '" + emailID + "', '" + phoneNumber + "', '"
                        + TaxID + "', '" + customerAddress + "', '" + customerPassword +"');";

            custTX.exec(qu);
            custTX.commit();

            qu = "SELECT customerid FROM customer WHERE taxid = '" + TaxID + "';";

            pqxx::nontransaction custNTX(customer);

            pqxx::result R(custNTX.exec(qu));

            for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
                cout << "\n\n" << string(18, ' ') << "This is your CustomerID: " << c[0].as<int>() << endl;
            }
            sleep(5);

        } catch (std::exception const &e)
        {
            std::cerr << "ERROR: " << e.what() << '\n';
        }

        system("clear");

        cout << "\n\n\n" << string(15, ' ') << "You are officialy our client!" << endl;
        cout << string(21, ' ') << "Thank you\n\n";

        goBackFun();
    }
}

int getCustomerID (const string& TaxID) {
    try {

        pqxx::connection customer("dbname=BMS");

        string qu = "SELECT customerid FROM customer WHERE taxid = '" + TaxID + "';";

        pqxx::nontransaction custNTX(customer);

        pqxx::result R(custNTX.exec(qu));

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            return c[0].as<int>();
        }

    } catch (std::exception const &e)
    {

        std::cerr << "ERROR: " << e.what() << '\n';

    }

    return 0;
}

bool fetchAccountDetails (int customerID) {
    try {
        pqxx::connection customer("dbname=BMS");
        pqxx::transaction custTX(customer);

        for (auto [accountID, customerid, accountType, currentBalance, dateOpened, accountStatus] : custTX.query<int, int, string, double, string, string>(
                "SELECT accountid, customerid, accounttype, currentbalance, dateopened, accountstatus FROM account WHERE customerid = '" +
                        to_string(customerID) + "';"
        )) {

            system("clear");
            cout << string(80, '=') << endl;
            cout << string(30, ' ') << "Account Details"<< endl;
            cout << string(80, '=') << "\n\n\n";

            cout << string(18, ' ') << "Customer ID: " << customerid << endl;
            cout << string(18, ' ') << "Account ID: " << accountID << endl;
            cout << string(18, ' ') << "Account Type: " << accountType << endl;
            cout << string(18, ' ') << "Current Balance: " << currentBalance << endl;
            cout << string(18, ' ') << "Date Opened: " << dateOpened << endl;
            cout << string(18, ' ') << "Account Status: " << accountStatus << endl;

            int goBack;
            cout << "\n\n" << string(3, ' ') << "Press 0 to exit or any number to go to Menu: ";
            cin >> goBack;
            if (goBack == 0) {
                exit(0);
            } else {
                return true;
            }
        }
    } catch (std::exception const &e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }

    return false;
}

void createAccount (const string& TaxID) {

    string accountType;
    int startingDepositAmount;

    if (checkTaxID(TaxID)) {

        int customerID = getCustomerID(TaxID);

        if (checkCustomerID(customerID)) {
            system("clear");

            cout << "\n\n\n" << string(15, ' ') << "You are already have an account!" << endl;
            cout << string(21, ' ') << "Thank you\n\n";

            goBackFun();
        } else {
            system("clear");
            cout << "\n\n" << string(15, ' ') << "You are our Customer!" << endl;
            cout << string(15, ' ') << "That's Great let us open an account for you!\n\n";

            cout << string(6, ' ') << "We need the following information to go forward:\n\n";

            cout << string(9, ' ') << "Only Saving possible. Enter \"saving\".\n";
            cout << string(9, ' ') << "Account Type: ";
            cin >> accountType;
            cout << endl;
            cout << string(9, ' ') << "If you don't want to add any money. Please press 0.\n";
            cout << string(9, ' ') << "Enter the amount to add into Account: ";
            cin >> startingDepositAmount;

            try {
                pqxx::connection account("dbname=BMS");

                pqxx::transaction accTX(account);

                string qu = "INSERT INTO account (customerid, accounttype, currentbalance, dateopened, accountstatus) VALUES ("
                            + to_string(customerID) + ", '" + accountType + "', " + to_string(startingDepositAmount)
                            + ", CURRENT_DATE, TRUE);";

                accTX.exec(qu);
                accTX.commit();

                fetchAccountDetails(customerID);

            } catch (std::exception const &e)
            {

                std::cerr << "ERROR: " << e.what() << '\n';

            }
        }

    } else {

        system("clear");
        cout << "\n\n" << string(21, ' ') << "The TaxID is not available!" << endl;
        cout << string(21, ' ') << "Error in the System!" << endl;

        cout << "\n\n" << string(21, ' ') << "Please Try Again!\n\n" << endl;

    }

    goBackFun();

}

#endif //BMS_ACCOUNTCREATION_H
