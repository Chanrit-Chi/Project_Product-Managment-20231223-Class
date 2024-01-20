#include <iostream>
#include <string>
#include "Product.cpp"
#include "Validator.cpp"

using namespace std;

class NewProduct : public Product
{
private:
    string ManufacturingDate;
    int WarrantyPeriod;

public:
    Validator validator;
    NewProduct()
    {
        this->WarrantyPeriod = 0;
    }

    NewProduct(int WarrantyPeriod)
    {
        this->WarrantyPeriod = WarrantyPeriod;
    }

    ~NewProduct(){};

    void SetWarrantyPeriod(const string &ManufacturingDate)
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
};