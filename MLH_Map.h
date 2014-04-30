#include <iostream>
#include "ML_hash.h"

using std::cout;
using std::endl;
using std::ostream;

const int HASH_RANGE = 5; // ML_hash returns 1-5
const int NUM_ROWS = 8;   // ML_hash supports levels 1-8

template <typename T>
class MLH_Map {

    class Node {
    public:
        Node();
        ~Node();

        int keys[HASH_RANGE];
        T* pvalues[HASH_RANGE];
        Node* children[HASH_RANGE];
        int size; // # entries in leaf, or sum of sizes of immediate children in stem (aka
                  // the number of actual entries contained in the subtree with this node
                  // as the root)
        
        bool is_empty() const; 
        bool is_stem() const;
        bool is_open() const;

        int put(const int key, T * const pvalue);
        int key_index(const int key) const;

        T* delete_at_index(const int index);

    };

    // print tree
    template <typename U>
    friend ostream &operator<<(ostream &output, const MLH_Map< U > &m);

public:
    MLH_Map();
    ~MLH_Map();

    int MLH_height() const;
    int MLH_size() const;
    int MLH_num_nodes() const;
    int MLH_steps() const;

    bool MLH_get_print_option() const;
    void MLH_set_print_option(const bool to);

    int MLH_insert(const int key, T * const pvalue);
    T* MLH_delete(const int key);
    T* MLH_get(const int key) const;

    void raw_print() const;

private:
    Node* const root;
    bool print_entries;
    int widths[NUM_ROWS + 1]; // # hash nodes in each row (widths[0] always = 1)
    static int steps; // effort spent. Declared static as a workaround the fact that
                      // we increment steps in functions declared 'const' (i.e. get).
    
    void expand(Node * const n, const int level); // aka explode
    void collapse(Node * const n, const int level);

    // NULL if failure
    int subtree_insert(Node * const n, const int level, const int key, T * const pvalue);
    int subtree_delete(Node * const n, const int level, const int key, T** ppvalue);
    T* subtree_get(Node * const n, const int level, const int key) const;
    ostream &subtree_print(ostream &output, Node * const n) const;
};

#include "MLH_Map_Node.cpp"
#include "MLH_Map.cpp"
