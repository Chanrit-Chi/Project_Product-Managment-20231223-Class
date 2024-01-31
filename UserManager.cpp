#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "User.cpp"
#include <algorithm>
using namespace std;

class UserManager
{
private:
    vector<User> users;
    string loggedInUser;

public:
    // bool login()
    // {
    //     string username, password;
    //     cout << "\tEnter username: ";
    //     cin >> username;
    //     cout << "\tEnter password: ";
    //     cin >> password;

    //     for (const User &user : users)
    //     {
    //         if (user.getName() == username && user.getPassword() == password)
    //         {
    //             cout << "\tWelcome, " << username << "!" << endl;
    //             return true;
    //         }
    //     }

    //     system("cls");
    //     cout << "\n"
    //          << "\tUser not found or invalid credentials.\n"
    //          << endl;
    //     return false;
    // }

    bool
    login(vector<User> &users)
    {
        string enteredUsername, enteredPassword;
        cout << "\tEnter username: ";
        cin >> enteredUsername;
        cout << "\tEnter password: ";
        cin >> enteredPassword;

        for (const User &user : users)
        {
            string storedUsername = user.getName();
            string storedPassword = user.getPassword();
            if (storedUsername == enteredUsername && storedPassword == enteredPassword)
            {
                loggedInUser = user.getName();
                return true;
            }
        }
        system("cls");
        cout << "\tUser not found or invalid credentials." << endl;
        return false;
    }

    void userRegister()
    {
        string username, password, address, phone;

        cout << "\tEnter username: ";
        cin >> username;

        // Check if username already exists
        for (const User &user : users)
        {
            if (user.getName() == username)
            {
                cout << "\tUsername already exists. Please choose a different username." << endl;
                return;
            }
        }

        cout << "\tEnter password: ";
        cin >> password;
        cin.ignore();
        cout << "\tEnter address: ";
        getline(cin, address);
        cout << "\tEnter phone: ";
        cin >> phone;

        users.emplace_back(username, password, address, phone);

        ofstream fOut("UserData.dat", ios::app); // Append mode to add a new user
        if (!fOut.is_open())
        {
            cerr << "\tCannot open UserData.dat" << endl;
            return;
        }

        fOut << username << " " << password << " " << address << " " << phone << endl;

        fOut.close();

        cout << "\tAccount created\n"
             << endl;
    }
    void LoadUser(vector<User> &users)
    {
        ifstream inputFile("UserData.dat");
        if (!inputFile.is_open())
        {
            cerr << "\tCannot open UserData.dat" << endl;
            return;
        }

        users.clear(); // Clear existing users

        string username, password, address, phone;
        while (inputFile >> username >> password >> address >> phone)
        {
            users.emplace_back(username, password, address, phone);
        }

        inputFile.close();

        cout << "\tUser data loaded successfully\n"
             << endl;
    }
};
