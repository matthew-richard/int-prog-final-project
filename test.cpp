#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"
#include "Hybrid.h"
#include "Task.h"

int main() {
    //Hybrid h = Hybrid::menu_constructor();
    //cout << h;
    Task t = Task::task_menu();
    cout << t;
    //((Car)c).print(cout);
    /*((Vehicle)c).print(cout);
    Vehicle v = c;
    v.print(cout);*/
}
