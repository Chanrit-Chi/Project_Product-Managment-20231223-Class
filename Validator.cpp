#pragma once
#include <iostream>
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
    {
        int input;
        while (true)
        {
            try
            {
                if (!(cin >> input))
                {
                    throw runtime_error("Invalid input. Please enter a valid integer.");
                }
                break; // Break the loop if the input is valid
            }
            catch (const exception &e)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << e.what() << " Please try again: ";
            }
        }
        return input;
    }

    // Validate input Enumeration
    bool isValidType(char newTypeChar)
    {
        while (true)
        {
            try
            {
                Type type;
                switch (tolower(newTypeChar))
                {
                case 'n':
                    type = Type::New;
                    return true;
                case 'u':
                    type = Type::Used;
                    return true;
                default:
                    throw invalid_argument("Invalid product type! Please try again.");
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tEnter a valid product type (n/N or u/U): ";
                cin >> newTypeChar;
            }
        }
    }

    // Validate char type
    char isValidCharType()
    {
        char choice;
        do
        {
            try
            {
                cout << "\tEnter your choice: ";
                cin >> choice;
                choice = tolower(choice);
                if (choice != 'y' && choice != 'n')
                {
                    throw invalid_argument("Invalid choice. Please enter y for Yes or n for No.");
                }
                break; // Break the loop if the input is valid
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        } while (true);
        return choice;
    }
};