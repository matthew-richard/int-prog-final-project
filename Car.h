#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

class Car : public Vehicle {
public:
    Car(Vehicle v, int e_s, string g_t, double e_p)
      : Vehicle(v),
        engine_size(e_s),
        gas_type(g_t),
        engine_pollution(e_p) {}

    static Car menu_constructor();

    ostream& print(ostream& out) const;

    int engine_size;
    string gas_type;
    double engine_pollution;
};

#endif
