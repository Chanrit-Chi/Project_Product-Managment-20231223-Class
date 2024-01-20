#include <iostream>
#include "ProductManager.cpp"

using namespace std;

class Product
{
public:
    virtual void AddProduct(vector<Product *> *products) = 0;
    virtual void ViewProduct(vector<Product *> *products) const = 0;
    virtual void SearchProduct(const std::vector<Product *> &products, int id) = 0;
    virtual void SearchProductMenu(const std::vector<Product *> &products) = 0;
};
