#include "Motorcycle.h"

Motorcycle Motorcycle::menu_constructor() {
    Vehicle v = Vehicle::menu_constructor();

    int engine_size = acceptPositive<int>("engine size (cc)");
    double front_wheel_size = acceptPositive<double>("front wheel size");
    double back_wheel_size = acceptPositive<double>("back wheel size");

    return Motorcycle(v, engine_size, front_wheel_size, back_wheel_size);
}

ostream& Motorcycle::print(ostream& out) const {
    out << (Vehicle) *this
        << "/ engine_size: " << engine_size << "cc"
        << " / front wheel size: " << front_wheel_size
        << " / back wheel size: " << back_wheel_size
        << endl;
    return out;
}

