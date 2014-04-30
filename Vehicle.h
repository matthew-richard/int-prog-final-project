#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>

#include "Menu_helpers.h"

using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

class Vehicle {
    friend ostream &operator<<(ostream &out, const Vehicle &v);
public:
    Vehicle(const int i, const int y, const string c, const double m)
      : id(i), year(y), color(c), mileage(m) {}

    static Vehicle menu_constructor();

    virtual ostream& print(ostream& out) const;

    const int id;
    int year;
    const string color;
    const double mileage;
};
#endif
