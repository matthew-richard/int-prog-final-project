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
    Car(const Vehicle &v, const double e_s, const string g_t, const double e_p)
      : Vehicle(v),
        engine_size(e_s),
        gas_type(g_t),
        engine_pollution(e_p) {}

    static Car menu_constructor();

    ostream& print(ostream& out) const;

    const double engine_size;
    const string gas_type;
    const double engine_pollution;
};

#endif
