#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "User.cpp"

using namespace std;

class UserManager
{
private:
    vector<User> users;

public:
    bool login()
    {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (const User &user : users)
        {
            if (user.getName() == username && user.getPassword() == password)
            {
                cout << "Welcome, " << username << "!" << endl;
                return true;
            }
        }

        cout << "User not found or invalid credentials." << endl;
        return false;
    }

    void userRegister()
    {
        string username, password, address, phone;

        cout << "Enter username: ";
        cin >> username;

        // Check if username already exists
        for (const User &user : users)
        {
            if (user.getName() == username)
            {
                cout << "Username already exists. Please choose a different username." << endl;
                return;
            }
        }

        cout << "Enter password: ";
        cin >> password;
        cout << "Enter address: ";
        cin >> address;
        cout << "Enter phone: ";
        cin >> phone;

        users.emplace_back(username, password, address, phone);

        ofstream fOut("UserData.dat", ios::app); // Append mode to add a new user
        if (!fOut.is_open())
        {
            cerr << "Cannot open UserData.dat" << endl;
            return;
        }

        fOut << username << " " << password << " " << address << " " << phone << endl;

        fOut.close();

        cout << "Account created" << endl;
    }
};
