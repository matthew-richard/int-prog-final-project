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

        int keys[HASH_RANGE];
        T* pvalues[HASH_RANGE];
        Node* children[HASH_RANGE];
        int size; // # entries in leaf, or sum of sizes of immediate children in stem (aka
                  // the number of actual entries contained in the subtree with this node
                  // as the root)
        
        bool is_empty() const; 
        bool is_stem() const;
        bool is_open() const;

        int put(int key, T* pvalue);
        int key_index(int key) const;

        int delete_at_index(int index);

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
    void MLH_set_print_option(bool to);

    T* MLH_insert(int key, const T &v);
    int MLH_delete(int key);
    T* MLH_get(int key);

    void raw_print();

private:
    Node* const root;
    bool print_entries;
    int widths[NUM_ROWS + 1]; // # hash nodes in each row (widths[0] always = 1)
    int steps; // effort spent
    
    void expand(Node* n, int level); // aka explode
    void collapse(Node* n, int level);

    // NULL if failure
    T* subtree_insert(Node* n, int level, int key, const T &v);
    int subtree_delete(Node* n, int level, int key);
    T* subtree_get(Node* n, int level, int key);
    void subtree_destroy(Node* n);
    ostream &subtree_print(ostream &output, Node* n) const;
};

#include "MLH_Map_Node.cpp"
#include "MLH_Map.cpp"
