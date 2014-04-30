#ifndef VSC_H
#define VSC_H

#include "MLH_Map.h"
#include "Record.h"
#include "Vehicle.h"
#include "List.h"

class VehicleServiceCenter {
public:
    VehicleServiceCenter() { records.MLH_set_print_option(true); }

    Record* add_vehicle(Vehicle * const v, const string type);
    bool checkout(const int id);
    bool add_task(const int id);
    bool print_vehicle(const int id) const;
    void print_vehicles() const;

    void menu();
private:
    MLH_Map<Record> records;

    void print_menu() const;
    string select_type() const;
    Vehicle* allocate_type(const string type) const;
    int read_id() const;
};

#endif
