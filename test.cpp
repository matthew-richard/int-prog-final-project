#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"
#include "Hybrid.h"
#include "Task.h"
#include "Record.h"
#include "List.h"
#include "VehicleServiceCenter.h"

int main() {
   /* List<Task> l;
    l.Insert(Task::MAINTENANCE);
    l.Insert(Task::BRAKE_CHANGE);
    l.Insert(Task::TUNE_UP);
    cout << l;*/

   /* Task q = Task(Task::MAINTENANCE);
    cout << q;*/

    VehicleServiceCenter vsc;
    vsc.menu();
    /*Hybrid* h = new Hybrid(Hybrid::menu_constructor());
    vsc.add_vehicle(h, "Hybrid");
    h = new Hybrid(Hybrid::menu_constructor());
    vsc.add_vehicle(h, "Hybrid");
    vsc.print_vehicles();*/
    /*Record r(h, "Hybrid");
    Task t = Task::task_menu();
    cout << t;
    r.add_task(t);
    t = Task::task_menu();
    r.add_task(t);
    cout << r.tasks;
    cout << r;*/
    //((Car)c).print(cout);
    /*((Vehicle)c).print(cout);
    Vehicle v = c;
    v.print(cout);*/
}
