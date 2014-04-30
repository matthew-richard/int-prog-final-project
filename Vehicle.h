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
    Vehicle(const int y, const string c, const double m)
      : year(y), color(c), mileage(m), type("Vehicle") {}

    static Vehicle menu_constructor();

    virtual ostream& print(ostream& out) const;
    string get_type() const { return type; }

    const int year;
    const string color;
    const double mileage;
protected:
    string type;
};
#endif
