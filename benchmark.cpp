#include <sstream>
#include <iostream>

#include "MLH_Map.h"
#include "random_op.h"

using std::cout;
using std::endl;
using std::istringstream;

int main(int argc, char** argv) {
    int range = 100;
    int ops = 1000;
    int seed = 1;
    bool content = true;

    Random_operation r;
    MLH_Map<int> m;

    int num_gets = 0;
    int num_dels = 0;
    int num_inss = 0;

    if (argc != 1 && argc != 3 && argc != 4)
        return 1;

    if (argc > 1) {
        istringstream(argv[1]) >> range;
        content = (range <= 100) ? true : false;
        istringstream(argv[2]) >> ops;

        if (argc >= 4)
            istringstream(argv[3]) >> seed;
    }

    cout << "range: " << range << " ops: " << ops << " seed: " << seed << " print_entries:" << content << endl;

    m.MLH_set_print_option(content);
    r = Random_operation(seed, range);

    for (int i = 1; i <= ops; i++) {
        int key;
        char op;
        r.Randomize_next_op();
        key = r.Get_key();
        op = r.Get_op();
        switch(op) {
            case 'G':
                m.MLH_get(key);
                num_gets++;
                break;
            case 'D':
                delete m.MLH_delete(key);
                num_dels++;
                break;
            case 'I':
                m.MLH_insert(key, new int(i));
                num_inss++;
                break;
        }
        if (i % (ops/10) == 0) {
            cout << endl << "printing after op " << i << ":" << m;
        }
    }
    cout << "gets: " << num_gets << " dels: " << num_dels << " inss: " << num_inss << endl
         << "STEPS: " << m.MLH_steps() << endl;
}
