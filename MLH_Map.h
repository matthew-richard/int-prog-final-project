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
                keys[i] = -1; 
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
        widths[0] = 1;
        for(int i = 1; i <= NUM_ROWS; i++) {
            widths[i] = 0;
        }
        steps = 0;
    }

    ~MLH_Map() {
        
    }

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
    int MLH_delete(int key) {
        Node* crumbs[NUM_ROWS + 1];
        int num_crumbs;
        int last_hash;
        int index = find_with_breadcrumbs(key, (Node**)crumbs, &num_crumbs, &last_hash);
        Node* top = crumbs[num_crumbs - 1];

        if (index < 0)
            return -1;

        delete top->pvalues[index]; // delete statically allocated data

        // replace entry being deleted by the last entry in the node
        if (index != top->size - 1) {
            top->keys[index] = top->keys[top->size - 1];
            top->pvalues[index] = top->pvalues[top->size - 1];
        }
        top->keys[top->size - 1] = -1; 
        (top->size)--;

        if (top->size == 0 && top != root) {
            delete top;
            widths[num_crumbs - 1]--;
            crumbs[num_crumbs - 2]->children[last_hash] = NULL;
        }

        for (int i = num_crumbs - 2; i >= 0; i--) {
            (crumbs[i]->size)--;
            if (crumbs[i]->size < HASH_RANGE) {
                collapse(crumbs[i], i);
            }
        }
    }

    // NULL if not found.
    int MLH_get(int key, T* out) {
        Node* crumbs[NUM_ROWS + 1];
        int num_crumbs;
        int last_hash;
        int index = find_with_breadcrumbs(key, (Node**)crumbs, &num_crumbs, &last_hash);

        if (index < 0) {
            return 0;
        } else {
            *out = *(crumbs[num_crumbs - 1]->pvalues[index]);
            return 1;
        }
    }

private:
    Node* root;
    bool print_entries;
    int widths[NUM_ROWS + 1]; // # hash nodes in each row (widths[0] always = 1)
    int steps; // effort spent

    bool is_stem(Node* n) {
        return n->size >= HASH_RANGE;
    }
    
    int key_index_in(int key, Node* n) {
        for (int i = 0; i < n->size; i++) {
            if (key == n->keys[i])
                return i; 
        }
        return -1;
    }

    void expand(Node* n, int level) {
        int new_children = 0;
        int hash;
        for (int i = 0; i < HASH_RANGE; i++) {
            hash = ML_hash(level + 1, n->keys[i]) - 1;
            if (n->children[hash] == NULL) {
                n->children[hash] = new Node();
                new_children++;
            }
            n->children[hash]->put(n->keys[i], n->pvalues[i]);
        }
        widths[level + 1] += new_children;
        if (new_children == 1)
            expand(n->children[hash], level + 1);
    }

    void collapse(Node* n, int level) {
        Node* child;
        int deleted_children = 0;
        n->size = 0;
        for (int i = 0; i < HASH_RANGE; i++) {
            child = n->children[i];
            if (child == NULL)
                continue;
            n->children[i] = NULL;

            // copy keys and pvalues to parent
            for (int j = 0; j < child->size; j++) {
                n->keys[n->size] = child->keys[j];
                n->pvalues[n->size] = child->pvalues[j];
                n->size++;
            }

            delete child;
            deleted_children++;
        }
        widths[level + 1] -= deleted_children;
    }

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
                index = key_index_in(key, n);
                break;
            }

            *hash = ML_hash(*num_crumbs, key) - 1;
            child = n->children[*hash];
        } while (child != NULL);

        return index;
    }
};
