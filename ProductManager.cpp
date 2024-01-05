#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>
#include "Product.cpp"

using namespace std;

class ProductManager
{
private:
    string ProductName;
    double Price;
    int StockIN;

public:
    void AddProduct(Product *products[], int &ProductCount)
    {
        int NextProductID = 1 + ProductCount;
        products[ProductCount] = new Product(NextProductID, "", 0.0, 0);
        cout << "Enter Product Name: ";
        cin >> ProductName;
        products[ProductCount]->setProductName(ProductName);
        cout << "Enter product price: ";
        cin >> Price;
        products[ProductCount]->setPrice(Price);
        cout << "Enter product stock: ";
        cin >> StockIN;
        products[ProductCount]->setStock(StockIN);
        ProductCount++;
    }
    void Delete_Product(Product *products[], int ProductCount)
    {
        for (int i = 0; i < ProductCount; ++i)
        {
            delete products[i];
        }
    }
    void AddProductMENU(Product *products[], int &ProductCount)
    {
        char add_more = 'y';
        do
        {
            std::cout << "Selected option: Add product \n\n";
            // call the AddProduct function to ask for the product information and add it to the array
            AddProduct(products, ProductCount);
            std::cout << "\nProduct added!\n"
                      << std::endl;
            std::cout << "Do you want to add more product?(y/n): " << std::endl;
            std::cin >> add_more;
        } while (add_more == 'y' || add_more == 'Y');
    }
};
