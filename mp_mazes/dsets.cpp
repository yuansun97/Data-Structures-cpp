/* Your code here! */

#include "dsets.h"

// Constructors
DisjointSets::DisjointSets() {
    ;
}

DisjointSets::DisjointSets(const DisjointSets & other) {
    _elems.assign(other._elems.begin(), other._elems.end());
}

DisjointSets & DisjointSets::operator=(const DisjointSets & other) {
    if (this == &other) return *this;
    _elems.assign(other._elems.begin(), other._elems.end());
    return *this;
}


/**
 * Creates n unconnected root nodes at the end of the vector.
 * 
 * @param num The number of nodes to create.
 * */
void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        _elems.push_back(-1);
    }
}

/**
 * Find the root index of a given element.
 * This function should compress paths during 
 * tracking back of recursions.
 * 
 * @param elem The index of elem to find root of.
 * @return the index of the root of he up-tree 
 * in which the parameter elem resides.
 * */
int DisjointSets::find(int elem) {
    if (_elems[elem] < 0) return elem;
    int root = find(_elems[elem]);
    _elems[elem] = root;
    return root;
}

/**
 * Setunion for two sets using union-by-size.
 * 
 * That is, the smaller sets (in terms of number of nodes) 
 * should point at the larger one.
 * 
 * The arguments to setunion might not be the roots,
 * so this function should find the roots of the given parms
 * before setunion.
 * 
 * If the two sets are the same size, make the second set 
 * point to the first set.
 * 
 * @param a Index of the first elements to union.
 * @param b Index of the second elements to union.
 * */
void DisjointSets::setunion(int a, int b) {
    int size_a = size(a);
    int size_b = size(b);
    int root_a = find(a);
    int root_b = find(b);
    if (size_a < size_b) {
        // root_a -> root_b
        _elems[root_a] = root_b;
        _elems[root_b] = 0 - (size_a + size_b);
    } else {
        // root_b -> root_a
        _elems[root_b] = root_a;
        _elems[root_a] = 0 - (size_a + size_b);
    }
}

/**
 * Return the number of nodes in the up-tree 
 * containing the given elem.
 * 
 * @param elem 
 * @return the number of nodes in the up-tree 
 * containing the given elem
 * */
int DisjointSets::size(int elem) {
    int root = find(elem);
    return 0 - _elems[root];
}

void DisjointSets::clearDSet() {
    _elems.clear();
}