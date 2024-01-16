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

public:
    void run()
    {

        int choice;
        char choice1;
        do
        {
            cout << "\t Please choose an option (1-2): ";
            choice = ValidInput.getValidInput();
            cout << "Product Management Menu: \n"
                 << "1. Add Product\n"
                 << "2. Update Product\n"
                 << "3. Search Product\n"
                 << "4. View Product\n"
                 << "5. Sort Product\n"
                 << "6. Delete Product\n"
                 << "0. Exit" << endl;
            switch (choice)
            {
            case 1:
            {
                ProdManager.AddProduct(Products);
                break;
            }

            default:
                break;
            }
            cout << "Do you want to perform another operation? (y/n): ";
            cin >> choice1;
        } while (choice1 == 'y' || choice1 == 'Y');
    }
};