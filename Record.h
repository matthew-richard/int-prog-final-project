#ifndef RECORD_H
#define RECORD_H

#include "List.h"
#include "Vehicle.h"
#include "Task.h"

class Record {
friend ostream& operator<<(ostream& out, Record &r);
public:
    Record(Vehicle * const veh, string t)
      : v(veh) , type(t), cost(0) {}

    Vehicle* v;
    string type;
    List<Task> tasks;
    double cost;

    void add_task(const Task &t);
};

#endif
