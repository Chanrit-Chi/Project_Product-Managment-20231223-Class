#include <iostream>
#include <string>
#include "Product.cpp"
#include "Validator.cpp"

using namespace std;

enum class Condition
{
    Good,
    SlightlyGood,
    Bad
};
class UsedProduct : public Product
{
private:
    Condition condition;
    Validator validator;

public:
    UsedProduct() : condition(Condition::Good) {}

    UsedProduct(Condition initialCondition) : condition(initialCondition) {}

    ~UsedProduct(){};

    void setCondition(Condition NewCondition)
    {
        if (validator.isValidCondition(NewCondition))
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
