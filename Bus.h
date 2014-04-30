#ifndef BUS_H
#define BUS_H

#include "Car.h"

#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

class Bus : public Car {
public:
    Bus(const Car &c, const int p_c)
      : Car(c),
        passenger_capacity(p_c) {}

    static Bus menu_constructor();

    ostream& print(ostream& out) const;

    const int passenger_capacity;
};

#endif
