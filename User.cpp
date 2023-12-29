// This implement only for the input field
// ID, name, ......
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Validator.cpp"
using namespace std;

class User
{
private:
    string name;
    string password;
    string address;
    string phone;

public:
    User() // Default constructor
    {
        this->name = "Unknow";
        this->password = "***";
        this->address = "Unknown";
        this->phone = "###########";
    }
    // Parameterize constructor

    User(string name, string password, string address, string phone)
    {
        this->name = name;
        this->password = password;
        this->address = address;
        this->phone = phone;
    }

    // copy constructor
    User(const User &user)
    {
        this->name = user.name;
        this->password = user.password;
        this->address = user.address;
        this->phone = user.phone;
    }

    ~User(){};

    void setName(const string &name)
    {
        if (Validator::isValidName(name))
        {
            this->name = name;
        }
        else
        {
            cout << "Name can not be emptied. Please enter a name." << endl;
        }
    }
    string getName() const
    {
        return name;
    }
    void setPassword(const string &password)
    {
        if (Validator::isValidPassword(password))
        {
            this->password = password;
        }
        else
        {
            cout << "Password must be at least 5 or more length" << endl;
        }
    }
    string getPassword() const
    {
        return password;
    }
    void setAddress(const string address)
    {
        if (Validator::isValidAddress(address))
        {
            this->address = address;
        }
        else
        {
            cout << "Address can not be empties, please enter an address" << endl;
        }
    }
    string getAddress() const
    {
        return address;
    }
    void setPhone(const string phone)
    {
        if (Validator::isValidPhone(phone))
        {
            this->phone = phone;
        }
        else
        {
            cout << "Invalid phone number format. Please use numeric characters only." << endl;
        }
    }

    string getPhone() const
    {
        return phone;
    }
};