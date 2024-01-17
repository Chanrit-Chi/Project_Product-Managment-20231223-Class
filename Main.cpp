#include <iostream>
#include <unistd.h>
#include "Application.cpp"

using namespace std;

int main()
{
    Application app;
    app.run();
    cout << "\n\tSaving your data..." << endl;
    sleep(2);
    cout << "\tData saved successfully!" << endl;

    return 0;
}