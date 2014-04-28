#ifndef VSC_H
#define VSC_H

#include "MLH_Map.h"
#include "Record.h"
#include "Vehicle.h"
#include "List.h"

class VehicleServiceCenter {
public:
    VehicleServiceCenter() { records.MLH_set_print_option(true); }

    Record* add_vehicle(Vehicle* v, string type);
    bool checkout(int id);
    bool add_task(int id);
    bool print_vehicle(int id);
    void print_vehicles();

    void menu();
private:
    MLH_Map<Record> records;

    void print_menu();
    string select_type();
    Vehicle* allocate_type(string type);
    int read_id();
};

#endif
