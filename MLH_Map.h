#include <iostream>
#include "ML_hash.h"

using std::cout;
using std::ostream;

const int HASH_RANGE = 5;
const int NUM_ROWS = 8;

template <typename T>
class MLH_Map {

    class Node {
    public:
        Node() {
            for (int i = 0; i < HASH_RANGE; i++) {
                children[i] = NULL;
            }
            size = 0;
        }

        int keys[HASH_RANGE];
        T* pvalues[HASH_RANGE];
        Node* children[HASH_RANGE];
        int size; // # entries in leaf, or sum of sizes of immediate children in stem

        int put(int key, T* pvalue) {
            if (size >= HASH_RANGE)
                return 0;

            keys[size] = key;
            pvalues[size] = pvalue;
            size++;
            return 1;
        }
    };

    friend ostream &operator<<(ostream &output, MLH_Map &m) {//, const MLH_Map &m) {
        output << "HI";
        return output;
    }

public:
    MLH_Map() {
        root = new Node();
        print_entries = false;
        for(int i = 0; i <= NUM_ROWS; i++) {
            widths[i] = 0;
        }
        steps = 0;
    }
    ~MLH_Map() { }

    int MLH_height() {
        for (int i = NUM_ROWS; i >= 0; i--) {
            if (widths[i] != 0) {
                return i;
            }
        }
    }

    int MLH_size() {
        return root->size;
    }

    void MLH_set_print_option(bool to) {
        print_entries = to;
    }

    // 0 if failure, 1 if success. Inserts only if
    // key isn't already present.
    int MLH_insert(int key, T v) {
        T* pvalue = new T(v); // copy to static memory

        Node* crumbs[NUM_ROWS + 1];
        int num_crumbs;
        int last_hash;
        int index = find_with_breadcrumbs(key, (Node**)crumbs, &num_crumbs, &last_hash);

        Node* top = crumbs[num_crumbs - 1];
        if (index == -1) { // last node checked was a leaf; put in that node
            top->put(key, pvalue);
            if (top->size >= HASH_RANGE)
                expand(top, num_crumbs - 1);
        } else if (index == -2) { // ... was a stem; make child and put in there
            Node* child = new Node();
            top->children[last_hash] = child;
            widths[num_crumbs]++;
            child->put(key, pvalue);
            (top->size)++;
        } else {
            return 0;
        }

        // Update sizes for the remaining members of the stack
        for (int i = num_crumbs - 2; i >= 0; i--) {
            (crumbs[i]->size)++;
        }
    }

    // 0 if failure, 1 if success.
    int MLH_delete(int key) { return 0; }

    // NULL if not found.
    T MLH_get(int key) { return NULL; }


private:
    Node* root;
    bool print_entries;
    int widths[NUM_ROWS + 1]; // # hash nodes in each row (widths[0] always = 1)
    int steps; // effort spent

    bool is_stem(Node* n) {
        return n->size >= HASH_RANGE;
    }
    
    int index_in(int key, int keys[HASH_RANGE]) {
        for (int i = 0; i < HASH_RANGE; i++) {
            if (key == keys[i])
                return i; 
        }
        return -1;
    }

    void expand(Node* n, int level) { }

    void collapse(Node* n, int level) { }

    int find_with_breadcrumbs(int key, Node** crumbs, int* num_crumbs, int* hash) {
        Node* n;
        Node* child = root;
        *num_crumbs = 0; // num_crumbs - 1 = current level
        int index = -2; // 'index' defaults to "left off at stem" signal

        do {
            n = child;

            crumbs[*num_crumbs] = n;
            (*num_crumbs)++;

            if(!is_stem(n)) {
                index = index_in(key, n->keys);
                break;
            }

            *hash = ML_hash(*num_crumbs, key) - 1;
            child = n->children[*hash];
        } while (child != NULL);

        return index;
    }
};
