#include "VehicleServiceCenter.h"
#include "Task.h"
#include "Vehicle.h"
#include "Car.h"
#include "Hybrid.h"
#include "Motorcycle.h"
#include "Bus.h"


Record* VehicleServiceCenter::add_vehicle(Vehicle* v, string type) {
    Record* result = records.MLH_insert(v->id, Record(v, type));
    if (result == NULL) {
        cout << "Error: There's already a vehicle with that id"
             << " in the service center!" << endl;
    } else {
        cout << type << " with id " << v->id << " successfully"
             << " arrived at service center." << endl;
    }
    return result;
}

bool VehicleServiceCenter::print_vehicle(int id) {
    Record* r = records.MLH_get(id);
    if (r == NULL) {
        cout << "Error: Couldn't find vehicle with id " << id << "!";
        return false;
    }
    cout << r->type << " with id " << id << " is as follows:" << endl
         << *(r->v)
         << endl;
    return true;
}

void VehicleServiceCenter::print_vehicles() {
    cout << "The vehicles in the service center are as follows:" << endl << endl;
    records.raw_print();
}

bool VehicleServiceCenter::checkout(int id) {
    Record* r = records.MLH_get(id);
    if (r == NULL) {
        cout << "Error: Couldn't find vehicle with id " << id << "!";
        return false;
    }

    cout << "Checking out vehicle with id " << id << ". Bill below." << endl;
    
    cout << *r;

    records.MLH_delete(r->v->id);
    cout << "Checkout successful."
         << endl;
    return true;
}

bool VehicleServiceCenter::add_task(int id) {
    Task t;
    Record* r = records.MLH_get(id);
    if (r == NULL) {
        cout << "Error: Couldn't find vehicle with id " << id << "!";
        return false;
    }

    t = Task::task_menu();

    r->add_task(t);

    cout << "Added the following task to vehicle with id " << id << ":" << endl
         << t
         << endl;
    return true;
}

string VehicleServiceCenter::select_type() {
    cout << "What type?" << endl
         << "0) Vehicle" << endl
         << "1) Car"     << endl
         << "2) Hybrid"  << endl
         << "3) Motorcycle" << endl
         << "4) Bus"     << endl;
    int input = -1;
    string types[5] = {"Vehicle", "Car", "Hybrid", "Motorcycle", "Bus"};

    while (input < 0) {
        cout << "Input: ";
        cin >> input;
        cin.ignore(1000, '\n');
        if (input < 0 || input > 4) {
            cout << "Invalid input! Please reenter." << endl;
            input = -1;
        }
    }
    
    return types[input];
}

Vehicle* VehicleServiceCenter::allocate_type(string type) {
    if (type == "Vehicle")
        return new Vehicle(Vehicle::menu_constructor());
    else if (type == "Car")
        return new Car(Car::menu_constructor());
    else if (type == "Bus")
        return new Bus(Bus::menu_constructor());
    else if (type == "Motorcycle")
        return new Motorcycle(Motorcycle::menu_constructor());
    else if (type == "Hybrid")
        return new Hybrid(Hybrid::menu_constructor());
    return NULL;
}

int VehicleServiceCenter::read_id() {
    int id = 0;
    while (!id) {
        cout << "Id?: ";
        cin >> id;
        cin.ignore(1000, '\n');

        if (records.MLH_get(id) == NULL) {
            cout << "No vehicle with that id! Please reenter." << endl;
            id = 0;
        }
    }
    return id;
}

void VehicleServiceCenter::print_menu() {
    cout << endl
         << "Vehicle Service Ctr: What would you like to do?" << endl
         << "0) Exit" << endl
         << "1) Add vehicle" << endl
         << "2) Checkout vehicle" << endl
         << "3) Add task to vehicle" << endl
         << "4) Print all vehicles" << endl
         << "5) Print a specific vehicle" << endl;
}

void VehicleServiceCenter::menu() {
    int input = 0;

    while (input >= 0) {
        Vehicle* v;
        string type;
        
        print_menu();

        cout << "Input: ";
        cin >> input;
        cin.ignore(1000, '\n');

        switch(input) {
            case 0:
                cout << "Exiting..." << endl;
                input = -1;
                break;
            case 1:
                type = select_type();
                v = allocate_type(type);
                add_vehicle(v, type);
                break;
            case 2:
                if (records.MLH_size() != 0) {
                    checkout(read_id());                    
                } else
                    cout << "The service center is empty!" << endl;
                break;
            case 3:
                if (records.MLH_size() != 0) {
                    add_task(read_id());                    
                } else
                    cout << "The service center is empty!" << endl;
                break;
            case 4:
                print_vehicles();
                break;
            case 5:
                if (records.MLH_size() != 0) {
                    print_vehicle(read_id());                    
                } else
                    cout << "The service center is empty!" << endl;
                break;
            default:
                cout << "Invalid input! Please reenter." << endl;
                input = 0;
                break;
        }
    }
}
