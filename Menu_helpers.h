#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cin;

template <typename T>
T acceptPositive(string varName) {
    T var = -1;
    while (var < 0) {
        cout << varName << "?: ";
        cin >> var;
        cin.ignore(1000, '\n');
        if (var < 0)
            cout << "Input not positive! Please reenter." << endl;
    }
    return var;
}

template <typename T>
T acceptInRange(string varName, T lo, T hi) {
    T var = -1;
    while(var == -1) {
        cout << varName << "?: ";
        cin >> var;
        cin.ignore(1000, '\n');
        if (var < lo || var > hi) {
            cout << "Not in range " << lo << "-" << hi << "! Please reenter." << endl;
            var = -1;
        }
    }
    return var;
}

#endif
