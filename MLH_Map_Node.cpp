template <typename T>
MLH_Map< T >::Node::Node() {
    for (int i = 0; i < HASH_RANGE; i++) {
        keys[i] = -1; 
        children[i] = NULL;
    }
    size = 0;
}

template <typename T>
bool MLH_Map< T >::Node::is_empty() const { return size == 0; }

template <typename T>
bool MLH_Map< T >::Node::is_stem() const { return size > HASH_RANGE; }

template <typename T>
bool MLH_Map< T >::Node::is_open() const { return size < HASH_RANGE; }

template <typename T>
int MLH_Map< T >::Node::put(int key, T* pvalue) {
    keys[size] = key;
    pvalues[size] = pvalue;
    size++;
    return 1;
}

template <typename T>
int MLH_Map< T >::Node::key_index(int key) const {
    for (int i = 0; i < size; i++) {
        if (key == keys[i])
            return i; 
    }
    return -1;
}

template <typename T>
int MLH_Map< T >::Node::delete_at_index(int index) {
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
template <typename T>
void MLH_Map< T >::Node::subtree_destroy() {
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
template <typename T>
ostream& MLH_Map< T >::Node::print(ostream &output) const {
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
