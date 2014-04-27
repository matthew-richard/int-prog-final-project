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
    Vehicle(int i, int y, string c, double m)
      : id(i), year(y), color(c), mileage(m) {}

    static Vehicle menu_constructor();

    virtual ostream& print(ostream& out) const;

    int id;
    int year;
    string color;
    double mileage;
};
#endif
