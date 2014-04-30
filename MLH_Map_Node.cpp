/* MLH_Map's Node subclass definitions */

template <typename T>
MLH_Map< T >::Node::Node() {
    for (int i = 0; i < HASH_RANGE; i++) {
        keys[i] = -1; 
        children[i] = NULL;
    }
    size = 0;
}

// deletes node and any children AND DATA attached to it.
// calling this on the root of a tree deletes the entire tree.
template <typename T>
MLH_Map< T >::Node::~Node() {
    if (is_stem()) {
        for (int i = 0; i < HASH_RANGE; i++) {
            if (children[i] != NULL)
                delete children[i];
        }
    } else {
        for (int i = 0; i < size; i++)
            delete pvalues[i];
    }
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
T* MLH_Map< T >::Node::delete_at_index(int index) {
    T* pvalue = pvalues[index];

    // replace entry being deleted with last entry in the node
    if (index != size - 1) {
        keys[index] = keys[size - 1];
        pvalues[index] = pvalues[size - 1];
    }
    keys[size - 1] = -1;
    size--;

    return pvalue;
}

