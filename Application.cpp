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
        do
        {
            cout << "\t\n\nProduct Management Menu: \n"
                 << "\t1. Add Product\n"
                 << "\t2. Update Product\n"
                 << "\t3. Search Product\n"
                 << "\t4. View Product\n"
                 << "\t5. Sort Product\n"
                 << "\t6. Delete Product\n"
                 << "\t0. Exit\n"
                 << endl;
            cout << "\tPlease choose an option: ";
            choice = ValidInput.getValidInput();
            cout << "\n"
                 << endl;
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
                return;
            }

            default:
                break;
            }
        } while (choice != 0);
    }
};