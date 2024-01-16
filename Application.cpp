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
    ProductManager ProdManager;
    Validator ValidInput;
    int ProductCount = 0;

public:
    void run()
    {
        int GetChoice()
        {
            int choice;
            cout << "\t Please choose an option (1-2): ";
            cin >> choice;
            return choice;
        };
        char choice;
        do
        {
            cout << "Product Management Menu: \n"
                 << "1. Add Product\n"
                 << "2. Update Product\n"
                 << "3. Search Product\n"
                 << "4. View Product\n"
                 << "5. Sort Product\n"
                 << "6. Delete Product\n"
                 << "0. Exit" << endl;
            int option = ValidInput.getValidInput();
            switch (option)
            {
            case 1:
            {
                ProdManager.AddProduct(Products);
                break;
            }

            default:
                break;
            }
        } while (choice == 'y' || choice == 'Y');
    }
};