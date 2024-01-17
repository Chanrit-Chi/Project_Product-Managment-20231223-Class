#include <iostream>
#include <chrono>
#include <thread>
#include "ProductManager.cpp"
#include "Product.cpp"
#include "UserManager.cpp"
#include "Application.cpp"

using namespace std;

int main()
{
    Application app;
    app.run();
    cout << "\nSaving your data..." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}