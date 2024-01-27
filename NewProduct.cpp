#pragma once
#include <iostream>
#include <string>
#include "Product.cpp"
#include "Validator.cpp"
#include "ProductDAO.cpp"

using namespace std;

class NewProduct : public Product
{
private:
    int WarrantyPeriod;
    Validator validator;

public:
    NewProduct() : WarrantyPeriod(0) {}

    NewProduct(int ProductID, string &ProductName, double Price, int Stock_in, Type type, int WarrantyPeriod) : Product(ProductID, ProductName, Price, Stock_in, Type::New), WarrantyPeriod(WarrantyPeriod)
    {
    }

    ~NewProduct(){};

    void SetWarrantyPeriod(int WarrantyPeriod)
    {
        if (validator.isValidWarrantyPeriod(WarrantyPeriod))
        {
            this->WarrantyPeriod = WarrantyPeriod;
        }
        else
        {
            cout << "\tInvalid input" << endl;
        }
    }

    int getWarrantyPeriod() const
    {
        return WarrantyPeriod;
    }

    void GetDisplay() const override
    {
        Product::GetDisplay();
        cout << "Warranty period: " << WarrantyPeriod << " months\n";
    }
};