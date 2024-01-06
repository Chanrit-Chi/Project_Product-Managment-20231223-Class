#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Product.cpp"
#include "Validator.cpp"

using namespace std;

class ProductManager
{
private:
    string ProductName;
    double Price;
    int StockIN;

public:
    void AddProduct(vector<Product *> &products)
    {
        int NextProductID = 1 + products.size();
        cout << "Enter Product Name: ";
        cin >> ProductName;
        // products[ProductCount]->setProductName(ProductName);
        cout << "Enter product price: ";
        cin >> Price;
        // products[ProductCount]->setPrice(Price);
        cout << "Enter product stock: ";
        cin >> StockIN;
        // products[ProductCount]->setStock(StockIN);
        products.push_back(new Product(NextProductID, ProductName, Price, StockIN));
    }
    void Delete_Product(Product *products[], int ProductCount)
    {
        for (int i = 0; i < ProductCount; ++i)
        {
            delete products[i];
        }
    }
    void AddProductMENU(vector<Product *> &products)
    {
        char add_more = 'y';
        do
        {
            std::cout << "Selected option: Add product \n\n";
            // call the AddProduct function to ask for the product information and add it to the array
            AddProduct(products);
            std::cout << "\nProduct added!\n"
                      << std::endl;
            std::cout << "Do you want to add more product?(y/n): " << std::endl;
            std::cin >> add_more;
        } while (add_more == 'y' || add_more == 'Y');
    }
    int searchByID(Product products[], int &count, int key)
    {

        for (int i = 0; i < count; i++)
        {
            if (products[i].getProductID() == key)
            {
                return i;
            }
        }
        return -1;
    }
    // Search product by name
    int searchByName(Product products[], int count, string key)
    {

        transform(key.begin(), key.end(), key.begin(), tolower);
        for (int i = 0; i < count; i++)
        {
            string productName = products[i].getProductName();
            transform(productName.begin(), productName.end(), productName.begin(), tolower);
            if (productName == key)
            {
                return i;
            }
        }
        return -1;
    }

    void update_product(Product products[], int num_products, int productID_to_update, string productName_to_update, bool searchByID)
    {
        int index_to_update = -1; // The index of the product in the array (initially set to -1 because to make sure there is index number at the start)
        transform(productName_to_update.begin(), productName_to_update.end(), productName_to_update.begin(), tolower);
        for (int i = 0; i < num_products; i++)
        {
            string productName = products[i].getProductName();
            transform(productName.begin(), productName.end(), productName.begin(), tolower);
            if ((searchByID && products[i].getProductID() == productID_to_update) || (!searchByID && productName == productName_to_update))
            {
                index_to_update = i;
                break;
            }
        }
        // Check if a product with the specified ID or name was found
        if (index_to_update != -1)
        {
            // ask the user what they want to update
            cout << "What do you want to update?\n"
                 << endl;
            cout << "1. Product ID" << endl;
            cout << "2. Product name" << endl;
            cout << "3. Product price" << endl;
            cout << "4. Product stock" << endl;
            cout << "0. Exit\n"
                 << endl;
            int option;
            Validator validateNum;
            option = validateNum.getValidInput();

            // update the product value based on the option
            switch (option)
            {
            case 1:
                cout << "Enter new product ID: ";
                products[index_to_update].setProductID(validateNum.getValidInput());
                break;
            case 2:
            {
                string ProdName;
                cout << "Enter new product name: ";
                cin >> ProdName;
                products[index_to_update].setProductName(ProdName);
                break;
            }
            case 3:
                double price;
                cout << "Enter new product price: ";
                cin >> price;
                products[index_to_update].setPrice(price);
                break;
            case 4:
                cout << "Enter new product stock: ";
                products[index_to_update].setStock(validateNum.getValidInput());
                break;
            case 0:
                break;
            default:
                cout << "Invalid option!" << endl;
            }
        }
        else
        {
            cout << "Product not found!" << endl;
        }
    }

    void DeleteProduct(vector<Product *> &products, int productIdToDelete)
    {
        auto it = find_if(products.begin(), products.end(),
                          [productIdToDelete](const Product *product)
                          {
                              return product->getProductID() == productIdToDelete;
                          });

        if (it != products.end())
        {
            // Product found, delete it
            delete *it;
            products.erase(it);
            cout << "Product deleted successfully." << endl;
        }
        else
        {
            cout << "Product not found." << endl;
        }
    }
};
