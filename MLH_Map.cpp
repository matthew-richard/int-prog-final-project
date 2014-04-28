/* MLH_Map definitions */

// print tree
template <typename T>
ostream &operator<<(ostream &output, const MLH_Map< T > &m) {
    output << endl << "***** MLH_MAP *****" << endl;

    output << "There are " << m.MLH_size() << " objects in the map." << endl
           << "There are " << m.MLH_num_nodes() << " nodes in the map's tree." << endl
           << "The tree is " << m.MLH_height() << " levels deep." << endl;
    
    if (m.print_entries) {
        output << endl << "The key-value pairs are as follows:" << endl;
        m.subtree_print(output, m.root);
    }

    output << "*****---------*****" << endl;
    return output;
}

template <typename T>
void MLH_Map<T>::raw_print() { subtree_print(cout, root); }

template <typename T>
MLH_Map< T >::MLH_Map()
  : root (new Node()),
    print_entries(false),
    steps(0)
{
    widths[0] = 1;
    for(int i = 1; i <= NUM_ROWS; i++) {
        widths[i] = 0;
    }
}

template <typename T>
MLH_Map< T >::~MLH_Map() { subtree_destroy(root); }

template <typename T>
int MLH_Map< T >::MLH_height() const {
    for (int i = NUM_ROWS; i >= 0; i--) {
        if (widths[i] != 0) {
            return i;
        }
    }
}

template <typename T>
int MLH_Map< T >::MLH_size() const { return root->size; }

template <typename T>
int MLH_Map< T >::MLH_num_nodes() const {
    int sum = 0;
    for (int i = 0; i < NUM_ROWS; i++) {
        sum += widths[i];
    }
    return sum;
}

template <typename T>
int MLH_Map< T >::MLH_steps() const { return steps; }

template <typename T>
bool MLH_Map< T >::MLH_get_print_option() const { return print_entries; }

template <typename T>
void MLH_Map< T >::MLH_set_print_option(bool to) { print_entries = to; }

// NULL if failure. Inserts only if
// key isn't already present.
template <typename T>
T* MLH_Map< T >::MLH_insert(int key, const T &v) { return subtree_insert(root, 0, key, v); }

// 0 if failure, 1 if success.
template <typename T>
int MLH_Map< T >::MLH_delete(int key) { return subtree_delete(root, 0, key); }

// NULL if not found.
template <typename T>
T* MLH_Map< T >::MLH_get(int key) { return subtree_get(root, 0, key); }

// aka explode
template <typename T>
void MLH_Map< T >::expand(Node* n, int level) {
    int new_children = 0;
    int hash;
    for (int i = 0; i < HASH_RANGE; i++) {
        hash = ML_hash(level + 1, n->keys[i]) - 1; steps++;
        if (n->children[hash] == NULL) {
            n->children[hash] = new Node();
            new_children++;
        }
        n->children[hash]->put(n->keys[i], n->pvalues[i]);
    }
    widths[level + 1] += new_children;
}

template <typename T>
void MLH_Map< T >::collapse(Node* n, int level) {
    Node* child;
    int deleted_children = 0;
    n->size = 0;
    for (int i = 0; i < HASH_RANGE; i++) {
        child = n->children[i]; steps++;
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
template <typename T>
T* MLH_Map< T >::subtree_insert(Node* n, int level, int key, const T &v) {
    T* result;
    int hash = 0;
    if (level < NUM_ROWS)
        hash = ML_hash(level + 1, key) - 1;
    Node* child = n->children[hash]; steps++;
    if (!n->is_stem()) {
        if (n->key_index(key) >= 0)
            return NULL;

        if (n->is_open()) {
            T* pvalue = new T(v); // copy to static memory
            n->put(key, pvalue);
            return pvalue;
        } else {
            // expand (explode) unavailable leaves
            expand(n, level);
            child = n->children[hash]; steps++;
            // force child if still missing
            if (child == NULL) {
                child = new Node();
                n->children[hash] = child; steps++;
                widths[level + 1]++;
            }
        }
    } else if (child == NULL) { // force child if missing from stem
        child = new Node();
        n->children[hash] = child; steps++;
        widths[level + 1]++;
    }

    result = subtree_insert(child, level + 1, key, v);
    if(result != NULL)
        (n->size)++;
    return result;
}

// 0 if failure, 1 if success (2 if success and 'n' was deleted)
template <typename T>
int MLH_Map< T >::subtree_delete(Node* n, int level, int key) {
    int result;
    int hash = 0;
    if (level < NUM_ROWS)
        hash = ML_hash(level + 1, key) - 1;
    Node* child = n->children[hash]; steps++;
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

// NULL if failure
template <typename T>
T* MLH_Map< T >::subtree_get(Node* n, int level, int key) {
    int hash = 0;
    if (level < NUM_ROWS)
        hash = ML_hash(level + 1, key) - 1;
    Node* child = n->children[hash]; steps++;
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

// deletes node and any data and children attached to it.
// calling this on the root of a tree deletes the entire tree.
template <typename T>
void MLH_Map< T >::subtree_destroy(Node* n) {
    if (n->is_stem()) {
        for (int i = 0; i < HASH_RANGE; i++) {
            if (n->children[i] != NULL)
                subtree_destroy(n->children[i]);
        }
    } else {
        for (int i = 0; i < n->size; i++) {
            delete n->pvalues[i];
        }
    }
    delete n;
}

// print entries in leafs of subtree with this node as a root
template <typename T>
ostream& MLH_Map< T >::subtree_print(ostream &output, Node* n) const {
    if (n->is_stem()) {
        for (int i = 0; i < HASH_RANGE; i++) {
            if (n->children[i] != NULL)
                subtree_print(output, n->children[i]);
        }
    } else {
        for (int i = 0; i < n->size; i++) {
            output << n->keys[i] << "\t: " << *(n->pvalues[i]) << endl;
        }
    }
    return output;
}
