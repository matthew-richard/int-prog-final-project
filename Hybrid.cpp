#include "Hybrid.h"

Hybrid Hybrid::menu_constructor() {
    Car c = Car::menu_constructor();

    int motor_power = acceptPositive<int>("motor power");
    double motor_usage = acceptPositive<double>("motor usage (hours)");
    double battery_capacity = acceptPositive<double>("battery capacity");;

    return Hybrid(c, motor_power, motor_usage, battery_capacity);
}

ostream& Hybrid::print(ostream& out) const {
    out << (Car) *this
        << "/ motor power: " << motor_power
        << " / motor usage: " << motor_usage << " hours"
        << " / battery capacity: " << battery_capacity
        << endl;
    return out;
}

