#include "Car.h"

Car Car::menu_constructor() {
    Vehicle v = Vehicle::menu_constructor();

    int engine_size = acceptPositive<int>("engine size (cc)");
    double engine_pollution = acceptInRange<double>("engine pollution %", 0, 100);
    string gas_type = "";

    cout << "gas type?"     << endl
         << "0) Premium"    << endl
         << "1) Plus"       << endl
         << "2) Regular"    << endl;
    while (gas_type == "") {
        int input;
        cout << "input: ";
        cin >> input;
        switch (input) {
            case 0:
                gas_type = "premium";
                break;
            case 1:
                gas_type = "plus";
                break;
            case 2:
                gas_type = "regular";
                break;
            default:
                cout << "Input invalid! Please reenter." << endl;
        }
    }

    return Car(v, engine_size, gas_type, engine_pollution);
}

ostream& Car::print(ostream& out) const {
    out << (Vehicle) *this
        << "/ engine size: " << engine_size << "cc"
        << " / gas type: " << gas_type
        << " / engine pollution: " << engine_pollution << "%"
        << endl;
    return out;
}

