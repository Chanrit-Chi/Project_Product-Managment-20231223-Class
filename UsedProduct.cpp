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
    UsedProduct() : condition(Condition::Good) {}

    UsedProduct(Condition initialCondition) : condition(initialCondition) {}

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
};
