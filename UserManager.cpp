#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include "User.cpp"
#include "Validator.cpp"
using namespace std;

class UserManager
{
private:
    vector<User> users;
    string loggedInUser;
    Validator validator;

public:
    UserManager()
    {
        LoadUser();
    }

    bool isLoggedIn() const
    {
        return !loggedInUser.empty();
    }

    void loggedOut()
    {
        cout << "\tLogging out user: " << loggedInUser << endl;
        loggedInUser = "";
    }

    bool login()
    {
        const int maxAttempts = 5;

        for (int attempt = 1; attempt <= maxAttempts; ++attempt)
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
                    system("cls");
                    return true; // Successful login
                }
            }

            // Incorrect credentials, allow for another attempt
            cout << "\tIncorrect username or password. Please try again." << endl;

            if (attempt == maxAttempts)
            {
                cout << "\tToo many login attempts. Exiting..." << endl;
                sleep(1);
                exit(0);
            }
        }

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
        saveUser();
        cout << "\tAccount created\n"
             << endl;
    }

    void LoadUser()
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

        // cout << "\tUser data loaded successfully\n"
        //<< endl;
    }

    void saveUser()
    {
        ofstream fOut("UserData.dat");
        if (!fOut.is_open())
        {
            cerr << "\tCannot open file for saving user." << endl;
            return;
        }

        for (const User &user : users)
        {
            fOut << user.getName() << ' ' << user.getPassword() << ' ' << user.getAddress() << ' ' << user.getPhone() << endl;
        }

        fOut.close();
    }

    void deleteAccount()
    {
        char choice;
        cout << "\tAre you sure you want to delete your account? y/n: " << endl;
        choice = validator.isValidCharType();
        if (choice == 'y')
        {
            string username, password;
            cout << "\tEnter your username: ";
            cin >> username;
            cout << "\tEnter password: ";
            cin >> password;

            auto it = remove_if(users.begin(), users.end(), [username, password](const User &user)
                                { return user.getName() == username && user.getPassword() == password; });
            if (it != users.end())
            {
                users.erase(it, users.end());
                saveUser();
                loggedInUser = "";
                loggedOut();
                cout << "\tAccount deleted successfully." << endl;
                return;
            }
            else
            {
                cout << "\tInvalid username or password. Your account cannot be deleted." << endl;
            }
        }
        else
        {
            cout << "\tAccount not deleted." << endl;
        }
    }

    void displayUserInfo(size_t index) const
    {
        if (index < users.size())
        {
            const User &user = users[index];
            cout << "\tAccount information." << endl;
            cout << "\tName: " << user.getName() << endl;
            cout << "\tPassword: " << user.getPassword() << endl;
            cout << "\tAddress: " << user.getAddress() << endl;
            cout << "\tPhone: " << user.getPhone() << endl;
        }
        else
        {
            cout << "\tInvalid index. User not found." << endl;
        }
    }
};
