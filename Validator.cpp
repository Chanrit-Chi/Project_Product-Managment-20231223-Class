#pragma once
#include <regex>
#include <string>
#include "UsedProduct.cpp"
using namespace std;

enum class Condition;
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
    static bool isValidCondition(Condition condition)
    {
        return condition >= Condition::Good && condition <= Condition::Bad;
    }
    // Validate Input numeric data
    int
    getValidInput()
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
};
