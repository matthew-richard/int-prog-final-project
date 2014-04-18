#include "MLH_Map.h"

using std::cout;

int main() {
    MLH_Map<int> m;
    std::cout << "height: " << m.MLH_height() << " size: " << m.MLH_size() << std::endl;
    cout << m; 

    m.MLH_insert(1, 15);
    m.MLH_insert(2, 20);
    m.MLH_insert(1, 30);
}
