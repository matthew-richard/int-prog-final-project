#include "VehicleServiceCenter.h"
#include "Menu_helpers.h"
#include "Task.h"
#include "Vehicle.h"
#include "Car.h"
#include "Hybrid.h"
#include "Motorcycle.h"
#include "Bus.h"


Record* VehicleServiceCenter::add_vehicle(Vehicle * const v) {
    Record* ins = new Record(v);
    int id = 0;
    int result = 0;
    while (!result) {
        id = read_id();
        result = records.MLH_insert(id, ins); 
        if (!result) {
            cout << "Error: There's already a vehicle with that id"
                 << " in the service center! Please reenter." << endl;
        }
    }

    cout << v->get_type() << " with id " << id << " successfully"
         << " arrived at service center." << endl;

    return ins;
}

bool VehicleServiceCenter::print_vehicle(const int id) const {
    Record* r = records.MLH_get(id);
    if (r == NULL) {
        cout << "Error: Couldn't find vehicle with id " << id << "!";
        return false;
    }
    cout << r->v->get_type() << " with id " << id << " is as follows:" << endl
         << *r
         << endl;
    return true;
}

void VehicleServiceCenter::print_vehicles() const {
    if (records.MLH_size() == 0) {
        cout << "There are no vehicles in the service center." << endl;
        return;
    }

    cout << endl
         << "The " << records.MLH_size() << " vehicles in the service"
         << " center are as follows:"
         << endl << endl
         << "ID ";
    records.raw_print();
}

bool VehicleServiceCenter::checkout(const int id) {
    Record* r = records.MLH_delete(id);
    if (r == NULL) {
        cout << "Error: Couldn't find vehicle with id " << id << "!";
        return false;
    }

    cout << "Checking out vehicle with id " << id << ". Bill below." << endl;
    
    cout << *r;
    revenues += r->cost;
    delete r;

    cout << "Checkout successful."
         << endl;
    vehicles_served++;
    return true;
}

bool VehicleServiceCenter::add_task(const int id) {
    Record* r = records.MLH_get(id);
    if (r == NULL) {
        cout << "Error: Couldn't find vehicle with id " << id << "!";
        return false;
    }
    add_task(r);
    return true;
}

void VehicleServiceCenter::add_task(Record * const r) {
    Task t = Task::task_menu();
    r->add_task(t);
    tasks_performed++;

    cout << "Added the following task:" << endl
         << t
         << endl << endl
         << "The " << r->v->get_type() << "'s updated info:"
         << *r;
}

void VehicleServiceCenter::print_stats() const {
    cout << endl
         << "Total revenues: \t$" << revenues << endl
         << "Vehicles served:\t" << vehicles_served << endl
         << "Tasks performed:\t" << tasks_performed << endl;
}

string VehicleServiceCenter::select_type() const {
    cout << endl
         << "What type?" << endl
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

Vehicle* VehicleServiceCenter::allocate_type(const string type) const {
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

int VehicleServiceCenter::read_id() const { return acceptInRange<int>("ID", 1, 100000); }

void VehicleServiceCenter::print_menu() const {
    cout << endl
         << "Vehicle Service Ctr: What would you like to do?" << endl
         << "0) Exit" << endl
         << "1) Add vehicle" << endl
         << "2) Checkout vehicle" << endl
         << "3) Add task to vehicle" << endl
         << "4) Print all vehicles (with ids)" << endl
         << "5) Print a specific vehicle" << endl
         << "6) View statistics" << endl;
}

void VehicleServiceCenter::menu() {
    int input = 0;

    while (input >= 0) {
        Vehicle* v = NULL;
        string type = "";
        Record* ins = NULL;
        
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
                ins = add_vehicle(v);
                if(ins != NULL)
                    add_task(ins);
                break;
            case 2:
                checkout(read_id());                    
                break;
            case 3:
                add_task(read_id());                    
                break;
            case 4:
                print_vehicles();
                break;
            case 5:
                print_vehicle(read_id());                    
                break;
            case 6:
                print_stats();
                break;
            default:
                cout << "Invalid input! Please reenter." << endl;
                input = 0;
                break;
        }
    }
}
