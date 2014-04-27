#ifndef HYBRID_H
#define HYBRID_H

#include "Car.h"

#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

class Hybrid : public Car {
public:
    Hybrid(Car c, int m_p, double m_u, double b_c)
      : Car(c),
        motor_power(m_p),
        motor_usage(m_u),
        battery_capacity(b_c) {}

    static Hybrid menu_constructor();

    ostream& print(ostream& out) const;

    int motor_power;
    double motor_usage; // Units: hours
    double battery_capacity;
};

#endif
