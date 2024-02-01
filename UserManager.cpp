#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "User.cpp"
#include <algorithm>
#include "Validator.cpp"
using namespace std;

class UserManager
{
private:
    vector<User> users;
    string loggedInUser;
    Validator validator;

public:
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
    void deleteAccount(vector<User> &users)
    {
        char choice;
        cout << "\tAre you sure you want to delete your account? y/n" << endl;
        choice = validator.isValidCharType();
        if (choice == 'y')
        {
            string username;
            string password;
            cout << "\tEnter your username: ";
            cin >> username;
            cout << "\tEnter password: ";
            cin >> password;
            bool found = false;
            for (auto &user : users)
            {
                if (user.getName() == username && user.getPassword() == password)
                {
                    users.erase(remove(users.begin(), users.end(), user), users.end());
                    cout << "\tAccount deleted successfully." << endl;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "\tInvalid username or password. Account not deleted." << endl;
            }
        }
        else
        {
            cout << "\tAccount not deleted." << endl;
        }
    }

    void updateBankAccount(vector<User> &users)
    {
        for (auto &user : users)
        {
            cout << "\tSelect the field you want to update: ";
            cout << "\t1. "
        }
    }
};
