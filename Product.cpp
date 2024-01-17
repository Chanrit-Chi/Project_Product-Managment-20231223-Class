// This implement only for the input field
// product name, code, price, stock in ......
#pragma once
#include "Validator.cpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Product
{
private:
    int productID;
    string ProductName;
    double price;
    int stock_in;

public:
    Validator validator;
    Product() // default constructor
    {
        this->productID = 0;
        this->ProductName = "Unknown";
        this->price = 0;
        this->stock_in = 0;
    }

    // parameterize constructor
    Product(int productID, string ProductName, double price, int stock_in)
    {
        this->productID = productID;
        this->ProductName = ProductName;
        this->price = price;
        this->stock_in = stock_in;
    }
    // copy constructor

    Product(const Product &prod)
    {
        this->productID = prod.productID;
        this->ProductName = prod.ProductName;
        this->price = prod.price;
        this->stock_in = prod.stock_in;
    }
    // destructor: best practice to use destructor
    ~Product(){};

    // setter and getter
    void setProductID(const int &productID)
    {
        if (validator.isValidProductID(productID))
        {
            this->productID = productID;
        }
        else
        {
            cout << "\tInvalid id" << endl;
        }
    }
    int getProductID() const
    {
        return productID;
    }
    void setProductName(const string ProductName)
    {
        if (validator.isValidProductName(ProductName))
        {
            this->ProductName = ProductName;
        }
        else
        {
            cout << "\tProduct name can not be emptied" << endl;
        }
    }
    string getProductName() const
    {
        return ProductName;
    }
    void setPrice(const double price)
    {
        if (validator.isValidPrice(price))
        {
            this->price = price;
        }
        else
        {
            cout << "\tInvalid price!" << endl;
        }
    }
    double getPrice() const
    {
        return price;
    }
    void setStock(const int stock_in)
    {
        if (validator.isValidStock(stock_in))
        {
            this->stock_in = stock_in;
        }
        else
        {
            cout << "\tInvalid stock number!" << endl;
        }
    }
    int getStock() const
    {
        return stock_in;
    }

    void GetDisplay() const
    {
        cout << getProductID() << setw(20)
             << getProductName() << setw(20)
             << getPrice() << setw(20) << getStock() << endl;
    }
    void GetDisplayHeader() const
    {
        cout << "Product ID " << setw(20) << "Product Name "
             << setw(20) << "Price" << setw(20) << "Stock " << endl;
    }
};