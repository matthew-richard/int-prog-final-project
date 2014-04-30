#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"

#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

class Motorcycle : public Vehicle {
public:
    Motorcycle(const Vehicle &v, const double e_s, const double f_w_s, const double b_w_s)
      : Vehicle(v),
        engine_size(e_s),
        front_wheel_size(f_w_s),
        back_wheel_size(b_w_s) {}

    static Motorcycle menu_constructor();

    ostream& print(ostream& out) const;

    const double engine_size;
    const double front_wheel_size;
    const double back_wheel_size;
};

#endif
