#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Product.cpp"
#include "Validator.cpp"
#include "UsedProduct.cpp"
#include "NewProduct.cpp"
#include "ConditionEnum.h"
#include <fstream>
#include <cctype>
using namespace std;

class ProductManager : public ProductDAO
{
private:
    string ProductName;
    double Price;
    int StockIN;
    Validator validateNum;
    Type type;
    vector<Product *> products;
    const string productDataFilename = "ProductData.txt";

public:
    void
    AddProduct(vector<Product *> &products) override
    {
        char add_more;
        do
        {
            int NextProductID = 1;
            if (!products.empty())
            {
                auto maxProductID = max_element(products.begin(), products.end(), [](const Product *a, const Product *b)
                                                { return a->getProductID() < b->getProductID(); });
                NextProductID = (*maxProductID)->getProductID() + 1;
            }
            cout << "\tEnter Product Name: ";
            cin >> ProductName;
            cout << "\tEnter product price: ";
            cin >> Price;
            cout << "\tEnter product stock: ";
            cin >> StockIN;

            cout << "\tIs the product new or used? (n/u): ";
            char productType;
            cin >> productType;
            Product *newProduct = nullptr;
            if (tolower(productType == 'n'))
            {
                cout << "\tEnter warranty period (month): ";
                int warrantyPeriod;
                warrantyPeriod = validateNum.getValidInput();
                newProduct = new NewProduct(NextProductID, ProductName, Price, StockIN, Type::New, warrantyPeriod);

                dynamic_cast<NewProduct *>(newProduct)->SetWarrantyPeriod(warrantyPeriod);
            }
            else if (tolower(productType) == 'u')
            {
                cout << "\tEnter condition (g/b for Good/Bad): ";
                char ConditionType;
                while (true)
                {
                    cin >> ConditionType;
                    ConditionType = tolower(ConditionType);
                    if (ConditionType == 'g' || ConditionType == 'b')
                    {
                        break;
                    }
                    cout << "\tInvalid input, please try again." << endl;
                }
                Condition condition;
                switch (ConditionType)
                {
                case 'g':
                    condition = Condition::Good;
                    break;
                case 'b':
                    condition = Condition::Bad;
                    break;
                default:
                    cout << "\tInvalid condition input. Using default (Good)." << endl;
                    condition = Condition::Good;
                    break;
                }
                newProduct = new UsedProduct(NextProductID, ProductName, Price, StockIN, Type::Used, condition);
            }
            if (newProduct != nullptr)
            {
                products.push_back(newProduct);

                cout << "\n\tProduct added!\n"
                     << endl;
            }

            cout << "\tDo you want to add more product?(y/n): ";
            cin >> add_more;
            if (tolower(add_more) == 'n')
            {
                return;
            }

        } while (true);
    }
    void DeleteProductForVector(vector<Product *> &products)
    {
        // Delete each product in the vector
        for (Product *product : products)
        {
            delete product;
        }
        products.clear();
    }

    void ViewProduct(const vector<Product *> &products) const override
    {
        if (products.empty())
        {
            cout << "\tProduct is empty. Please add some products." << endl;
            return;
        }

        cout << "\nView all products\n"
             << endl;
        products[0]->GetDisplayHeader();

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

    int searchProductMenu(const vector<Product *> &products) override
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

    void update_product(vector<Product *> &products) override
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
                cout << "\tProduct updated!" << endl;
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

    void DeleteProduct(vector<Product *> &products) override
    {
        bool search;
        string key;
        int indexToDelete = -1;
        cout << "\tSearch product id or name to delete: ";
        cin >> key;
        try
        {
            int searchChoice = stoi(key);
            indexToDelete = searchProduct(products, searchChoice);
        }
        catch (invalid_argument &) // Key is not a number
        {
            // Searching by name
            indexToDelete = searchProduct(products, key);
        }

        if (indexToDelete != -1)
        {
            char choice;
            do
            {
                cout << "\tAre you sure you want to delete? y/n: ";
                cin >> choice;
                if (tolower(choice) == 'y')
                {
                    delete products[indexToDelete];
                    products[indexToDelete] = products.back();
                    products.pop_back();
                    cout << "\tProduct deleted successfully." << endl;
                }
                else if (tolower(choice) == 'n')
                {
                    cout << "\tDeletion cancelled!" << endl;
                    return;
                }
                else
                {
                    cout << "\tInvalid choice." << endl;
                }
            } while (choice != 'n' || choice != 'y');
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

    void sortProduct(vector<Product *> &products) override
    {
        int choice = -1;
        cout << "\tProduct sorting:\n"
             << "\t1. Sort by ID\n"
             << "\t2. Sort by name\n"
             << "\t0. Exit\n";
        cout << "\n\tPlease select option for sorting: ";
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

        if (!products.empty())
        {
            products[0]->GetDisplayHeader();
        }
        for (auto product : products)
        {
            product->GetDisplay();
        }
    }

    void SaveProduct(const vector<Product *> &products) const override
    {
        ofstream outputFile("ProductData.txt", ios::app);
        if (!outputFile.is_open())
        {
            cout << "Error creating output file\n";
            exit(1);
        }

        for (const auto &product : products)
        {
            // Save product details to the file
            outputFile << product->getProductID() << ","
                       << product->getProductName() << ","
                       << product->getPrice() << ","
                       << product->getStock() << ","
                       << (product->getType() == Type::New ? "N" : "U"); // Save product type

            // Additional details based on product type
            if (product->getType() == Type::New)
            {
                outputFile << "," << dynamic_cast<const NewProduct *>(product)->getWarrantyPeriod();
            }
            else if (product->getType() == Type::Used)
            {
                outputFile << "," << static_cast<int>(dynamic_cast<const UsedProduct *>(product)->getCondition());
            }

            outputFile << "\n";
        }
        outputFile.close();
    }

    void LoadProduct(vector<Product *> &products) override
    {
        ifstream inputFile("ProductData.txt");
        if (!inputFile.is_open())
        {
            cout << "\tError opening ProductData.txt\n";
            return;
        }

        products.clear();

        string line;
        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string value;

            int productID, stock;
            double price;
            string productName, type;
            int additionalInfo = 0; // Default value in case conversion fails

            // Read each value separated by commas
            while (getline(iss, value, ','))
            {
                switch (value.size())
                {
                case 1:
                    // Assuming it's a single character (type)
                    type = value;
                    break;
                default:
                    // Attempt to convert to an integer for additionalInfo
                    if (all_of(value.begin(), value.end(), ::isdigit)) // Check if all characters are digits
                    {
                        additionalInfo = stoi(value);
                    }
                    else
                    {
                        // Handle the case when it's not a valid integer
                        cout << "\tSkipping non-integer value '" << value << "' for additionalInfo.\n";
                    }
                    break;
                case 2:
                    // Assuming it's a string or double
                    if (value.find('.') != string::npos)
                    {
                        // Assuming it's a double
                        price = stod(value);
                    }
                    else
                    {
                        // Assuming it's a string (productName)
                        productName = value;
                    }
                    break;
                }
            }

            // Create and add the product based on the parsed values
            Product *newProduct = nullptr;

            try
            {
                if (type == "N")
                {
                    newProduct = new NewProduct(productID, productName, price, stock, Type::New, additionalInfo);
                    dynamic_cast<NewProduct *>(newProduct)->SetWarrantyPeriod(additionalInfo);
                }
                else if (type == "U")
                {
                    newProduct = new UsedProduct(productID, productName, price, stock, Type::Used, static_cast<Condition>(additionalInfo));
                }

                if (newProduct != nullptr)
                {
                    products.push_back(newProduct);
                    cout << "Read: " << productID << " " << productName << " " << price << " " << stock << " " << type << " " << additionalInfo << " - Product added\n";
                }
                else
                {
                    cout << "Read: " << productID << " " << productName << " " << price << " " << stock << " " << type << " " << additionalInfo << " - Failed to create product\n";
                }
            }
            catch (const std::exception &e)
            {
                cout << "\tError creating product: " << e.what() << endl;
                for (const auto &product : products)
                {
                    delete product;
                }
                products.clear();
                return;
            }
        }

        inputFile.close();

        cout << "\tLoaded " << products.size() << " products." << endl;
    }
};
