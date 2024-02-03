#pragma once
#include <iostream>
#include <vector>
#include <unistd.h>
#include "Product.cpp"
#include "ProductManager.cpp"
#include "User.cpp"
#include "UserManager.cpp"
#include "Validator.cpp"

using namespace std;

class Application
{
private:
    vector<Product *> Products;
    vector<User> users;
    UserManager userManager;
    User user;
    Validator ValidInput;

public:
    ProductManager ProdManager;
    bool isLogin = false;
    void UserAuthenticationMenu()
    {
        cout << "\tWelcome to product management tool."
             << "\n"
             << endl;
        cout << "\tPlease register or login to continue." << endl;
        cout << "\t1. Create Account" << endl;
        cout << "\t2. Login" << endl;
        cout << "\t3. View Account info" << endl;
        cout << "\t4. Go to product menu" << endl;
        cout << "\t0. Exit" << endl;
    }
    void ProductMenu()
    {
        int choice;
        do
        {
            cout << "\n\tProduct Management Menu: \n"
                 << endl;
            cout << "\t1. Add Product\n"
                 << "\t2. Update Product\n"
                 << "\t3. Search Product\n"
                 << "\t4. View Product\n"
                 << "\t5. Sort Product\n"
                 << "\t6. Delete Product\n"
                 << "\t0. Exit\n"
                 << endl;
            cout << "\tPlease choose an option: ";
            choice = ValidInput.getValidInput();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice)
            {
            case 1:
            {
                ProdManager.AddProduct(Products);
                break;
            }
            case 2:
            {
                ProdManager.update_product(Products);
                break;
            }
            case 3:
            {
                ProdManager.searchProductMenu(Products);
                break;
            }
            case 4:
            {
                ProdManager.ViewProduct(Products);
                break;
            }
            case 5:
            {
                ProdManager.sortProduct(Products);
                break;
            }
            case 6:
            {
                ProdManager.DeleteProduct(Products);
                break;
            }
            case 0:
            {
                ProdManager.SaveProduct(Products);
                system("cls");
                return;
            }

            default:
                break;
            }
        } while (choice != 0);
    }

    void BeforeLoginMenu()
    {
        system("cls");
        cout << "\tWelcome to product management tool.\n"
             << "\tPlease register or login to continue.\n"
             << "\t1. Create Account\n"
             << "\t2. Login\n"
             << "\t0. Exit\n";
    }

    void AfterLoginMenu()
    {
        cout << "\n\tUser Management Menu:\n"
             << endl;
        cout << "\t1. Product Menu" << endl;
        cout << "\t2. View Account" << endl;
        cout << "\t3. Delete Account" << endl;
        cout << "\t0. Logout" << endl;
    }

    void run()
    {
        int choice;
        bool loggedIn = false;

        userManager.LoadUser();
        ProdManager.LoadProduct(Products);

        do
        {
            if (loggedIn)
            {
                // User is logged in
                AfterLoginMenu();
                cout << "\n\tEnter your choice: ";
                choice = ValidInput.getValidInput();

                switch (choice)
                {
                case 1:
                    ProductMenu();
                    system("cls");
                    break;
                case 2:
                    userManager.displayUserInfo(0);
                    cout << "\n\tPress Enter key to continue...";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    char enterKey;
                    cin.get(enterKey);
                    system("cls");
                    break;
                case 3:
                    userManager.deleteAccount();
                    loggedIn = false; // User logged out
                    system("cls");
                    break;
                case 0:
                    userManager.loggedOut();
                    system("cls");
                    loggedIn = false; // User logged out
                    break;
                default:
                    break;
                }
            }
            else
            {
                // User is not logged in
                BeforeLoginMenu();
                cout << "\n\tEnter your choice: ";
                int innerChoice;
                innerChoice = ValidInput.getValidInput();

                switch (innerChoice)
                {
                case 1:
                    userManager.userRegister();
                    system("cls");
                    loggedIn = true; // User registered/logged in
                    break;
                case 2:
                    while (!userManager.login())
                    {
                        cout << "\tUser not found or invalid credentials. Please try again.\n"
                             << endl;
                    }
                    loggedIn = true; // User registered/logged in
                    break;
                case 0:
                    cout << "\n\tSaving your data..." << endl;
                    sleep(1);
                    cout << "\tData saved successfully!" << endl;
                    break;
                default:
                    cout << "\tInvalid choice. Please try again." << endl;
                    break;
                }
            }

            // Display welcome menu after logging out or completing an action
            if (!loggedIn)
            {
                system("cls");
                BeforeLoginMenu();
            }

        } while (true);
    }
};