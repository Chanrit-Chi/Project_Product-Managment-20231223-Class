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
    // Destructor
    void Delete_Product(vector<Product *> &products)
    {
        // Delete each product in the vector
        for (Product *product : products)
        {
            delete product;
        }
        products.clear();
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

    // Function overloading to seach product by ID and name
    int searchProduct(const Product products[], int count, int id)
    {

        for (int i = 0; i < count; i++)
        {
            if (products[i].getProductID() == id)
            {
                return i;
            }
        }
        return -1;
    }
    // Search product by name
    int searchProduct(const Product products[], int count, string &name)
    {
        string lowerName = name;
        // transform(name.begin(), name.end(), name.begin(), tolower);
        for (int i = 0; i < count; i++)
        {
            string productName = products[i].getProductName();
            // transform(productName.begin(), productName.end(), productName.begin(), tolower);
            if (productName == lowerName)
            {
                return i;
            }
        }
        return -1;
    }

    int searchProductMenu(const Product products[], int count)
    {
        string UserInput;
        cout << "Please enter ID or name to seach: ";
        cin >> UserInput;
        try
        {
            int id = stoi(UserInput);
            int index = searchProduct(products, count, id);
            if (index != -1)
            {
                products[index].
            }
        }
        catch (const invalid_argument &)
        {
            return searchProduct(products, count, UserInput);
        }
        catch (const out_of_range &)
        {
            cout << "Input is out of range." << endl;
            return -1;
        }
    }

    void update_product(Product products[], int num_products, int productID_to_update, string productName_to_update, bool searchByID)
    {
        int index_to_update = -1; // The index of the product in the array (initially set to -1 because to make sure there is index number at the start)
        if (searchByID)
        {
            index_to_update = searchProduct(products, num_products, productID_to_update);
        }
        else
        {
            index_to_update = searchProduct(products, num_products, productName_to_update);
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

    void DeleteProduct(Product products[], int &count, string &key, bool searchByID)
    {
        int indexToDelete = -1;

        try
        {
            // Attempt to convert the key to an integer
            int id = stoi(key);

            // Call the appropriate search function based on searchByID
            if (searchByID)
            {
                indexToDelete = searchProduct(products, count, id);
            }
        }
        catch (invalid_argument &) // Key is not a number
        {
            // Searching by name
            indexToDelete = searchProduct(products, count, key);
        }

        if (indexToDelete != -1)
        {
            // Product found, delete it
            products[indexToDelete] = products[count - 1];
            count--;
            cout << "Product deleted successfully." << endl;
        }
        else
        {
            cout << "Product not found." << endl;
        }
    }

    // Sort product
};
