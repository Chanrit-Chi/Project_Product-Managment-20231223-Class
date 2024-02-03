#pragma once
#include <regex>
#include <string>
#include "ConditionEnum.h"
using namespace std;

class Validator

{
public:
    // Validation for User
    static bool isValidName(const string &getName)
    {
        return !getName.empty();
    }

    static bool isValidPassword(const string &getPassword)
    {
        return getPassword.length() >= 5;
    }

    static bool isValidAddress(const string &getAddress)
    {
        return !getAddress.empty();
    }

    static bool isValidPhone(const string &getPhone)
    {
        return regex_match(getPhone, regex("^[0-9]+$"));
    }

    // Validation for Product

    static bool isValidProductID(const int &getProductID)
    {
        return getProductID >= 0;
    }

    static bool isValidProductName(const string &getProductName)
    {
        return !getProductName.empty();
    }

    static bool isValidPrice(const double &getPrice)
    {
        return getPrice >= 0;
    }
    static bool isValidStock(const int &getStock)
    {
        return getStock >= 0;
    }
    static bool isValidWarrantyPeriod(const int &getWarrantyPeriod)
    {
        return getWarrantyPeriod >= 0;
    }
    bool isValidCondition(Condition condition)
    {
        switch (condition)
        {
        case Condition::Good:
        case Condition::Bad:
            return true;
        default:
            return false;
        }
    }
    // Validate Input numeric data
    int getValidInput()
    { // This is to put constrain on number input
        int input;
        while (!(cin >> input))
        {
            cin.clear();                                         // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "\tInvalid input. Please enter a valid option: ";
        }
        return input;
    }

    // Validate input Enumeration
    bool isValidType(char newTypeChar)
    {
        while (true)
        {

            Type type;
            if (cin >> newTypeChar)
            {
                switch (tolower(newTypeChar))
                {
                case 'n':
                    type = Type::New;
                    return true;
                case 'u':
                    type = Type::Used;
                    return true;
                default:
                    cout << "\tInvalid product type! Please try again." << endl;
                }
            }
            else
            {
                cout << "\tInvalid input! Please enter a single character (n/N or u/U)." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    // Validate char type
    char isValidCharType()
    {
        char choice;
        do
        {
            cout << "\tEnter your choice: ";
            cin >> choice;
            choice = tolower(choice);
            if (choice != 'y' && choice != 'n')
            {
                cout << "Invalid choice. Please enter y for Yes or n for No." << endl;
            }
        } while (choice != 'y' && choice != 'n');
        return choice;
    }
};