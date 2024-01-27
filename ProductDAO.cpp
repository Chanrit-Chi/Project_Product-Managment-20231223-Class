#include <iostream>

using namespace std;
class ProductDAO
{
public:
    virtual void AddProduct(vector<Product *> &products) = 0;
    virtual void ViewProduct(const vector<Product *> &products) const = 0;
    virtual int searchProductMenu(const vector<Product *> &products) = 0;
    virtual void update_product(vector<Product *> &products) = 0;
    virtual void DeleteProduct(vector<Product *> &products) = 0;
    virtual void sortProduct(vector<Product *> &products) = 0;
};
