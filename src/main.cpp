#include <iostream>
#include "mylib.hpp"

using namespace std;

int main()
{
    cout << mylib::add(10, 2) << endl;

    cout << mylib::add(10, 2) << endl;
    cout << mylib::sub(10, 2) << endl;
    cout << mylib::mul(10, 2) << endl;
    cout << mylib::div(10, 2) << endl;

    cout << mylib::add(1.0, 2.5) << endl;
    cout << mylib::sub(1.0, 2.5) << endl;
    cout << mylib::mul(1.0, 2.5) << endl;
    cout << mylib::div(1.0, 2.5) << endl;
}