#include "Bus.h"

Bus Bus::menu_constructor() {
    Car c = Car::menu_constructor();

    int passenger_capacity = acceptPositive<int>("passenger capacity");

    return Bus(c, passenger_capacity);
}

ostream& Bus::print(ostream& out) const {
    out << (Car) *this
        << "/ passenger capacity: " << passenger_capacity
        << endl;
    return out;
}

