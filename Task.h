#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::ostream;

class Task {
friend ostream& operator<<(ostream& out, Task t);
public:
    Task(string n, double p_c, double l_c)
      : name(n), parts_cost(p_c), labor_cost(l_c) {}

    static const Task MAINTENANCE;
    static const Task BRAKE_CHANGE;
    static const Task TUNE_UP;

    static Task menu_constructor();
    static Task task_menu();

    string name;
    double parts_cost;
    double labor_cost;
};

#endif
