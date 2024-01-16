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
            cout << "Product Management Menu: \n"
                 << "\t1. Add Product\n"
                 << "\t2. Update Product\n"
                 << "\t3. Search Product\n"
                 << "\t4. View Product\n"
                 << "\t5. Sort Product\n"
                 << "\t6. Delete Product\n"
                 << "\t0. Exit" << endl;
            cout << "\t Please choose an option (1-2): ";
            choice = ValidInput.getValidInput();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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