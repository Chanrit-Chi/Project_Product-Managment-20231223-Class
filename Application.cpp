#pragma once
#include <iostream>
#include <vector>
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
    ProductManager ProdManager;
    UserManager userManager;
    User user;
    Validator ValidInput;

public:
    bool isLogin = false;
    void UserAuthenticationMenu()
    {
        cout << "\tWelcome to product management tool."
             << "\n"
             << endl;
        cout << "\tPlease register or login to continue." << endl;
        cout << "\t1. Create Account" << endl;
        cout << "\t2. Login" << endl;
        cout << "\t0. Exit" << endl;
    }
    void ProductMenu()
    {
        // ProdManager.LoadProduct(Products);
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
                return;
            }

            default:
                break;
            }
        } while (choice != 0);
    }

    void run()
    {
        int choice = 0;
        userManager.LoadUser(users);
        do
        {
            UserAuthenticationMenu();
            cout << "\n"
                 << "\tEnter you choice: ";
            choice = ValidInput.getValidInput();
            switch (choice)
            {
            case 1:
                userManager.userRegister();
                break;
            case 2:
                if (userManager.login(users) == true)
                {
                    system("cls");
                    ProdManager.LoadProduct(Products);
                    ProductMenu();
                }
                break;
            case 0:
                exit(1);
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }

        } while (choice != 0);
    }
};