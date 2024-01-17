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
    Validator validateNum;

public:
    void AddProduct(vector<Product *> &products)
    {
        char add_more;
        do
        {
            int NextProductID = 1 + products.size();
            cout << "\tEnter Product Name: ";
            cin >> ProductName;
            cout << "\tEnter product price: ";
            cin >> Price;
            cout << "\tEnter product stock: ";
            cin >> StockIN;
            products.push_back(new Product(NextProductID, ProductName, Price, StockIN));
            cout << "\t\nProduct added!\n"
                 << endl;
            cout << "\tDo you want to add more product?(y/n): ";
            cin >> add_more;
            if (tolower(add_more) == 'n')
            {
                return;
            }

        } while (true);
    }
    void Delete_Product(vector<Product *> &products)
    {
        // Delete each product in the vector
        for (Product *product : products)
        {
            delete product;
        }
        products.clear();
    }

    void ViewProduct(const vector<Product *> &products) const
    {
        if (!products.empty())
        {
            cout << "\t\nView all products\n"
                 << endl;
            products[0]->GetDisplayHeader();
        }
        else
        {
            cout << "Product is empty. Please add some products." << endl;
        }
        for (const Product *product : products)
        {
            product->GetDisplay();
        }
    }

    // Function overloading to seach product by ID and name
    int searchProduct(const vector<Product *> &products, int id)
    {

        for (int i = 0; i < products.size(); i++)
        {
            if (products[i]->getProductID() == id)
            {
                return i;
            }
        }
        return -1;
    }
    // Search product by name
    int searchProduct(const vector<Product *> &products, string &name)
    {
        string lowerName = name;
        // transform(name.begin(), name.end(), name.begin(), tolower);
        for (int i = 0; i < products.size(); i++)
        {
            string productName = products[i]->getProductName();
            // transform(productName.begin(), productName.end(), productName.begin(), tolower);
            if (productName == lowerName)
            {
                return i;
            }
        }
        return -1;
    }

    int searchProductMenu(const vector<Product *> &products)
    {
        string UserInput;
        cout << "\tPlease enter ID or name to seach: ";
        cin >> UserInput;
        try
        {
            int id = stoi(UserInput);
            int index = searchProduct(products, id);
            if (index != -1)
            {
                products[index]->GetDisplayHeader();
                products[index]->GetDisplay();
            }
            else
            {
                cout << "\tProduct not found." << endl;
            }
        }
        catch (const invalid_argument &)
        {
            int index = searchProduct(products, UserInput);
            if (index != -1)
            {
                products[index]->GetDisplayHeader();
                products[index]->GetDisplay();
            }
            else
            {
                cout << "\tProduct not found." << endl;
            }
        }
        catch (const out_of_range &)
        {
            cout << "\tInvalid input. Please enter ID or Name of product." << endl;
            return -1;
        }
    }

    void update_product(vector<Product *> &products)
    {
        int productID_to_update;
        string productName_to_update;
        bool searchOption;
        int newProductID;

        cout << "\tSearch product for update by: "
             << "\n"
             << "\t1. Product ID\n"
             << "\t2. Product name\n"
             << "\t0. Exit"
             << endl;
        cout << "\n\tEnter your choice: ";
        int searchChoice = validateNum.getValidInput();
        switch (searchChoice)
        {
        case 1:
        {
            cout << "\tEnter Product ID to update: ";
            productID_to_update = validateNum.getValidInput();
            searchOption = true;
            break;
        }
        case 2:
        {
            cout << "\tEnter Product Name to update: ";
            cin >> productName_to_update;
            searchOption = false;
            break;
        }
        case 0:
        {
            return;
        }
        default:
            cout << "\tInvalid option" << endl;
        }
        // if (searchChoice == 1)
        // {
        //     cout << "\tEnter Product ID to update: ";
        //     productID_to_update = validateNum.getValidInput();
        //     // searchOption = true;
        // }
        // else if (searchChoice == 2)
        // {
        //     cout << "\tEnter Product Name to update: ";
        //     cin >> productName_to_update;
        //     searchOption = false;
        // }
        // else
        // {
        //     cout << "\tInvalid choice!" << endl;
        //     return;
        // }
        int index_to_update = -1; // The index of the product in the array (initially set to -1 because to make sure there is index number at the start)
        // Check if a product with the specified ID or name was found
        for (int i = 0; i < products.size(); i++)
        {
            Product *product = products[i];
            if ((searchOption && product->getProductID() == productID_to_update) || (!searchOption && product->getProductName() == productName_to_update))
            {
                index_to_update = i;
                break;
            }
        }

        if (index_to_update != -1)
        {
            // ask the user what they want to update
            cout << "\n\tWhat do you want to update?\n"
                 << endl;
            cout << "\t1. Product ID" << endl;
            cout << "\t2. Product name" << endl;
            cout << "\t3. Product price" << endl;
            cout << "\t4. Product stock" << endl;
            cout << "\t0. Exit\n"
                 << endl;
            cout << "\n\tPlease enter option to update: ";
            int option;
            option = validateNum.getValidInput();

            // update the product value based on the option
            switch (option)
            {
            case 1:
                cout << "\tEnter new product ID: ";
                newProductID = validateNum.getValidInput();
                products[index_to_update]->setProductID(newProductID); // Use -> for pointer dereferencing
                cout << "\t\nProduct updated!" << endl;
                break;
            case 2:
            {
                string ProdName;
                cout << "\tEnter new product name: ";
                cin >> ProdName;
                products[index_to_update]->setProductName(ProdName); // Use -> for pointer dereferencing
                cout << "\tProduct updated." << endl;
                break;
            }
            case 3:
            {
                double price;
                cout << "\tEnter new product price: ";
                cin >> price;
                products[index_to_update]->setPrice(price); // Use -> for pointer dereferencing
                cout << "\tProduct updated." << endl;
                break;
            }
            case 4:
            {
                cout << "\tEnter new product stock: ";
                int newStock = validateNum.getValidInput();
                products[index_to_update]->setStock(newStock); // Use -> for pointer dereferencing
                cout << "\tProduct updated." << endl;
                break;
            }
            case 0:
                break;
            default:
                cout << "\tInvalid option!" << endl;
            }
        }
        else
        {
            cout << "\tProduct not found!" << endl;
        }
    }

    void DeleteProduct(vector<Product *> &products)
    {
        bool searchByID;
        string key;
        int indexToDelete = -1;
        try
        {
            // Attempt to convert the key to an integer
            int id = stoi(key);

            // Call the appropriate search function based on searchByID
            if (searchByID)
            {
                indexToDelete = searchProduct(products, id);
            }
        }
        catch (invalid_argument &) // Key is not a number
        {
            // Searching by name
            indexToDelete = searchProduct(products, key);
        }

        if (indexToDelete != -1)
        {
            // Product found, delete it
            delete products[indexToDelete];
            products[indexToDelete] = products.back();
            products.pop_back();
            cout << "\tProduct deleted successfully." << endl;
        }
        else
        {
            cout << "\tProduct not found." << endl;
        }
    }

    // Sort product
    static bool compareByID(const Product *a, const Product *b)
    {
        return a->getProductID() < b->getProductID();
    };

    static bool compareByName(const Product *a, const Product *b)
    { // compare the list in array of product_list
        return a->getProductName() < b->getProductName();
    }

    void sortProduct(vector<Product *> &products)
    {
        int choice = -1;
        cout << "\t\nProduct sorting:\n"
             << "\t1. Sort by ID\n"
             << "\t2. Sort by name\n"
             << "\t0. Exit\n";
        cout << "\t\nPlease select option for sorting: "
             << "\n";
        choice = validateNum.getValidInput();

        if (choice != 0)
        {
            cout << "\t\nPlease select the sorting order:\n"
                 << "\t1. Sort by Ascending\n"
                 << "\t2. Sort by Descending\n"
                 << "\t0. Exit\n";
            int sortOption = validateNum.getValidInput();

            if (sortOption != 0)
            {
                switch (choice)
                {
                case 1:
                    sortAndDisplay(products, compareByID, "ID", sortOption);
                    break;
                case 2:
                    sortAndDisplay(products, compareByName, "Name", sortOption);
                    break;
                default:
                    break;
                }
            }
        }
    }

    template <typename CompareFunction>
    void sortAndDisplay(vector<Product *> &products, CompareFunction compare, const string &sortType, int sortOption)
    {
        sort(products.begin(), products.end(), compare);

        if (sortOption == 2)
        {
            reverse(products.begin(), products.end());
        }

        cout << "\t\nProduct sorted by " << sortType << (sortOption == 1 ? " in Ascending" : " in Descending") << " order\n"
             << endl;

        cout << "\t\nSorted products\n";
        if (!products.empty())
        {
            products[0]->GetDisplayHeader();
        }
        for (auto product : products)
        {
            product->GetDisplay();
        }
    }
};
