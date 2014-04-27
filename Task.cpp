#include "Task.h"
#include "Menu_helpers.h"

using std::getline;

const Task Task::MAINTENANCE = Task("maintenance", 1000, 2000);
const Task Task::BRAKE_CHANGE = Task("brake change", 500, 1000);
const Task Task::TUNE_UP = Task("tune up", 250, 500);

Task Task::task_menu() {
    int input;
    cout << "Choose your task to add:" << endl
         << "0) Maintenance"           << endl
         << "1) Brake Change"          << endl
         << "2) Tune Up"               << endl
         << "3) *custom task*"         << endl;
    while(1) {
        cout << "input: ";
        cin >> input;
        cin.ignore(1000, '\n');
        switch(input) {
            case 0:
                return MAINTENANCE;
                break;
            case 1:
                return BRAKE_CHANGE;
                break;
            case 2:
                return TUNE_UP;
                break;
            case 3:
                return menu_constructor();
                break;
            default:
                cout << "Invalid input! Please reenter." << endl;
        }
    }
}

Task Task::menu_constructor() {
    double parts_cost;
    double labor_cost;
    string name;

    cout << "name?: ";
    getline(cin, name);

    parts_cost = acceptPositive<int>("parts cost");
    labor_cost = acceptPositive<int>("labor cost");

    return Task(name, parts_cost, labor_cost);
}

ostream& operator<<(ostream& out, Task t) {
    out << "name: " << t.name
        << " / parts cost: $" << t.parts_cost
        << " / labor cost: $" << t.labor_cost
        << " / *total cost*: $" << t.parts_cost + t.labor_cost
        << endl;
    return out;
}
