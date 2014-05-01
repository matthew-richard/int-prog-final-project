#ifndef VSC_H
#define VSC_H

#include "MLH_Map.h"
#include "Record.h"
#include "Vehicle.h"
#include "List.h"

class VehicleServiceCenter {
public:
    VehicleServiceCenter()
      : revenues(0), vehicles_served(0), tasks_performed(0)
    { records.MLH_set_print_option(true); }

    Record* add_vehicle(Vehicle * const v);
    bool checkout(const int id);
    bool add_task(const int id);
    bool print_vehicle(const int id) const;
    void print_vehicles() const;

    void menu();
private:
    MLH_Map<Record> records;

    double revenues;
    int vehicles_served;
    int tasks_performed;

    void add_task(Record * const r);
    void print_menu() const;
    Vehicle* allocate_vehicle() const;
    int read_id() const;
    void print_stats() const;
};

#endif
