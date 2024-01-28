// User.cpp

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
    Validator validator;

public:
    // Default constructor
    User()
        : name("Unknown"), password("***"), address("Unknown"), phone("###########") {}

    // Parameterized constructor
    User(const string &name, const string &password, const string &address, const string &phone)
        : name(name), password(password), address(address), phone(phone) {}

    // Copy constructor
    User(const User &user)
        : name(user.name), password(user.password), address(user.address), phone(user.phone) {}

    // Destructor
    ~User() {}

    // Getter and setter methods
    void setName(const string &name)
    {
        if (validator.isValidName(name))
        {
            this->name = name;
        }
        else
        {
            cout << "Name cannot be empty. Please enter a name." << endl;
        }
    }

    string getName() const
    {
        return name;
    }

    void setPassword(const string &password)
    {
        if (validator.isValidPassword(password))
        {
            this->password = password;
        }
        else
        {
            cout << "Password must be at least 5 characters long." << endl;
        }
    }

    string getPassword() const
    {
        return password;
    }

    void setAddress(const string &address)
    {
        if (validator.isValidAddress(address))
        {
            this->address = address;
        }
        else
        {
            cout << "Address cannot be empty. Please enter an address." << endl;
        }
    }

    string getAddress() const
    {
        return address;
    }

    void setPhone(const string &phone)
    {
        if (validator.isValidPhone(phone))
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

    void displayUserInfo() const
    {
        cout << "Name: " << setw(20) << name
             << "Password: " << setw(20) << password
             << "Address: " << setw(20) << address
             << "Phone: " << setw(20) << phone << endl;
    }
};
