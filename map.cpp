#include "MLH_Map.h"

using std::cout;

int main() {
    MLH_Map<int> m;
    std::cout << "height: " << m.MLH_height() << " size: " << m.MLH_size() << std::endl;
    cout << m; 

    /*m.MLH_insert(1, 15);
    m.MLH_insert(2, 20);
    m.MLH_insert(3, 30);
    m.MLH_insert(4, 40);
    m.MLH_insert(5, 50);
    m.MLH_insert(6, 60);*/
    m.MLH_insert(5,100);
    m.MLH_insert(10,100);
    m.MLH_insert(15,100);
    m.MLH_insert(20,100);
    m.MLH_insert(25,100);

    cout << m.MLH_height();

    m.MLH_delete(25);
    
    cout << m.MLH_height();
    
    int g; m.MLH_get(1, &g);
    m.MLH_delete(2);
    int b = m.MLH_get(2, &g);
    b = m.MLH_get(1, &g);
    cout;
}
