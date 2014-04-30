#ifndef RECORD_H
#define RECORD_H

#include "List.h"
#include "Vehicle.h"
#include "Task.h"

class Record {
friend ostream& operator<<(ostream& out, Record &r);
public:
    Record(Vehicle * const veh)
      : v(veh), cost(0) {}
    ~Record();

    Vehicle * const v;
    List<Task> tasks;
    double cost;

    void add_task(const Task &t);
};

#endif
