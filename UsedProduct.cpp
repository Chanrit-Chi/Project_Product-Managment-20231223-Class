#pragma once
#include <iostream>
#include <string>
#include "Product.cpp"
#include "Validator.cpp"
#include "ConditionEnum.h"

using namespace std;

class UsedProduct : public Product
{
private:
    Condition condition;
    Validator validateEnum;

public:
    UsedProduct(int productID, string ProductName, double price, int stock_in, Type type, Condition initialCondition)
        : Product(productID, ProductName, price, stock_in, Type::Used), condition(initialCondition)
    {
    }

    ~UsedProduct(){};

    void setCondition(Condition NewCondition)
    {
        if (validateEnum.isValidCondition(NewCondition))
        {
            condition = NewCondition;
        }
        else
        {
            cout << "\tInvalid input condition" << endl;
        }
    }

    Condition getCondition() const
    {
        return condition;
    }

    void GetDisplay() const override
    {
        Product::GetDisplay();
        cout << "Condition: " << (condition == Condition::Good ? "Good" : "Bad") << endl;
    }
};
