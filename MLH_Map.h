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
        int size; // # entries in leaf, or sum of sizes of immediate children in stem (aka
                  // the number of actual entries contained in the subtree with this node
                  // as the root)
        
        bool is_empty() const { return size == 0; }
        bool is_stem() const { return size > HASH_RANGE; }
        bool is_open() const { return size < HASH_RANGE; }

        int put(int key, T* pvalue) {
            keys[size] = key;
            pvalues[size] = pvalue;
            size++;
            return 1;
        }
        int key_index(int key) const {
            for (int i = 0; i < size; i++) {
                if (key == keys[i])
                    return i; 
            }
            return -1;
        }

        // returns 1 if just the entry was deleted;
        // 2 if the whole node was deleted too
        int delete_at_index(int index) {
            delete pvalues[index]; // delete statically allocated data
    
            // replace entry being deleted by last entry in the node
            if (index != size - 1) {
                keys[index] = keys[size - 1];
                pvalues[index] = pvalues[size - 1];
            }
            keys[size - 1] = -1;
            size--;
        }

        // deletes node and any data and children attached to it.
        // calling this on the root of a tree deletes the entire tree.
        void subtree_destroy() {
            if (is_stem()) {
                for (int i = 0; i < HASH_RANGE; i++) {
                    if (children[i] != NULL)
                        children[i]->subtree_destroy();
                }
            } else {
                for (int i = 0; i < size; i++) {
                    delete pvalues[i];
                }
            }
            delete this;
        }

        // print entries in leafs of subtree with this node as a root
        ostream &print(ostream &output) const {
            if (is_stem()) {
                for (int i = 0; i < HASH_RANGE; i++) {
                    if (children[i] != NULL)
                        children[i]->print(output);
                }
            } else {
                for (int i = 0; i < size; i++) {
                    output << keys[i] << "\t: " << *pvalues[i] << endl;
                }
            }
            return output;
        }
    };

    // print tree
    friend ostream &operator<<(ostream &output, const MLH_Map &m) {
        output << endl << "***** MLH_MAP *****" << endl;

        output << "There are " << m.MLH_size() << " objects in the map." << endl
               << "There are " << m.MLH_num_nodes() << " nodes in the tree." << endl
               << "The tree is " << m.MLH_height() << " levels deep." << endl;
        
        if (m.print_entries) {
            output << endl << "The key-value pairs are as follows:" << endl;
            m.root->print(output);
        }

        output << endl << "*****---------*****" << endl;
        return output;
    }

public:
    MLH_Map()
      : root (new Node()),
        print_entries(false),
        steps(0)
    {
        widths[0] = 1;
        for(int i = 1; i <= NUM_ROWS; i++) {
            widths[i] = 0;
        }
    }

    ~MLH_Map() {
        root->subtree_destroy();
    }

    int MLH_height() const {
        for (int i = NUM_ROWS; i >= 0; i--) {
            if (widths[i] != 0) {
                return i;
            }
        }
    }

    int MLH_size() const { return root->size; }

    int MLH_num_nodes() const {
        int sum = 0;
        for (int i = 0; i < NUM_ROWS; i++) {
            sum += widths[i];
        }
        return sum;
    }

    bool MLH_get_print_option() const {
        return print_entries;
    }

    void MLH_set_print_option(bool to) {
        print_entries = to;
    }

    // 0 if failure, 1 if success. Inserts only if
    // key isn't already present.
    int MLH_insert(int key, const T &v) {
        return subtree_insert(root, 0, key, v);
    }

    // 0 if failure, 1 if success.
    int MLH_delete(int key) {
        return subtree_delete(root, 0, key); 
    }

    // 1 if found, 0 if not.
    int MLH_get(int key, T* out) const {
        T* result = subtree_get(root, 0, key);
        if (result == NULL) {
            return 0;
        } else {
            *out = *result;
            return 1;
        }
    }

private:
    Node* const root;
    bool print_entries;
    int widths[NUM_ROWS + 1]; // # hash nodes in each row (widths[0] always = 1)
    int steps; // effort spent
    
    // aka explode
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
            for (int j = 0; j < child->size; j++)
                n->put(child->keys[j], child->pvalues[j]);

            delete child;
            deleted_children++;
        }
        widths[level + 1] -= deleted_children;
    }

    // 0 if failure, 1 if success
    int subtree_insert(Node* n, int level, int key, const T &v) {
        int result;
        int hash = ML_hash(level + 1, key) - 1;
        Node* child = n->children[hash];
        if (!n->is_stem()) {
            if (n->is_open()) {
                if (n->key_index(key) >= 0)
                    return 0;

                T* pvalue = new T(v); // copy to static memory
                n->put(key, pvalue);
                return 1;
            } else {
                // expand (explode) unavailable leaves
                expand(n, level);
                child = n->children[hash];
                // force child if still missing
                if (child == NULL) {
                    child = new Node();
                    n->children[hash] = child;
                    widths[level + 1]++;
                }
            }
        } else if (child == NULL) { // force child if missing from stem
            child = new Node();
            n->children[hash] = child;
            widths[level + 1]++;
        }
        
        if(result = subtree_insert(child, level + 1, key, v))
            (n->size)++;
        return result;
    }

    // 0 if failure, 1 if success (2 if success and 'n' was deleted)
    int subtree_delete(Node* n, int level, int key) {
        int result;
        int hash = ML_hash(level + 1, key) - 1;
        Node* child = n->children[hash];
        if (!n->is_stem()) {
            int index = n->key_index(key);
            if (index < 0)
                return 0;

            n->delete_at_index(index);
            if (n->is_empty() && n != root) {
                delete n;
                widths[level]--;
                return 2;
            } else return 1;
        } else if (child == NULL) {
            return 0;
        }
        
        result = subtree_delete(child, level + 1, key);
        
        // check if child was deleted
        if (result == 2) {
            n->children[hash] = NULL;
            result = 1;
        }

        // update size. collapse if needed
        if (result > 0) {
            (n->size)--;
            if (n->size <= HASH_RANGE) {
                collapse(n, level);
            }
        }
        return result;
    }

    // 0 if failure, 1 if success
    T* subtree_get(Node* n, int level, int key) const {
        int hash = ML_hash(level + 1, key) - 1;
        Node* child = n->children[hash];
        if (!n->is_stem()) {
            int index = n->key_index(key); 
            if (index < 0)
                return NULL;
            else return n->pvalues[index];
        } else if (child == NULL) {
            return NULL;
        }
        
        return subtree_get(child, level + 1, key);
    }
};
