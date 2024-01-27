// This implement only for the input field
// product name, code, price, stock in ......
#pragma once
#include "Validator.cpp"
#include <iostream>
#include <iomanip>
#include <string>
#include "ConditionEnum.h"

using namespace std;

class Product
{
private:
    int productID;
    string ProductName;
    double price;
    int stock_in;
    Type type;

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
    Product(int productID, string ProductName, double price, int stock_in, Type type)
    {
        this->productID = productID;
        this->ProductName = ProductName;
        this->price = price;
        this->stock_in = stock_in;
        this->type = type;
    }
    // copy constructor

    Product(const Product &prod)
    {
        this->productID = prod.productID;
        this->ProductName = prod.ProductName;
        this->price = prod.price;
        this->stock_in = prod.stock_in;
        this->type = prod.type;
    }
    // destructor: best practice to use destructor
    virtual ~Product(){};

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
    void setType(char type)
    {
        if (validator.isValidType(static_cast<char>(type)))
        {
            Type validateType = static_cast<Type>(type);
            this->type = validateType;
        }
        else
        {
            cout << "\tInvalid type of product" << endl;
        }
    }
    Type getType() const
    {
        return type;
    }

    // virtual void GetDisplay() const
    // {
    //     cout << setw(5) << getProductID() << setw(20)
    //          << getProductName() << setw(10) << '$' << fixed
    //          << setprecision(2) << getPrice() << setw(15) << getStock(),
    //         getType();
    // }
    // virtual void GetDisplayHeader() const
    // {
    //     cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(15) << "Stock" << setw(15) << "Product Type"
    //          << "Details\n";
    //     cout << setfill('-') << setw(65) << "" << setfill(' ');
    // }
    virtual void GetDisplay() const
    {
        cout << left << setw(5) << getProductID()
             << setw(20) << getProductName()
             << "$" << fixed << setprecision(2) << setw(14) << getPrice()
             << setw(15) << getStock();

        if (getType() == Type::New)
        {
            cout << setw(15) << "New";
        }
        else if (getType() == Type::Used)
        {
            cout << setw(15) << "Used";
        }
    }

    void GetDisplayHeader() const
    {
        cout << left << setw(5) << "ID"
             << setw(20) << "Name"
             << setw(15) << "Price"
             << setw(15) << "Stock"
             << setw(15) << "Product Type" << setw(25)
             << "Details"
             << "\n"
             << endl;
    }
};