/* Your code here! */

#include <vector>

#pragma once

class DisjointSets {
    public:
    // constructor
    DisjointSets();

    DisjointSets(const DisjointSets & other);

    DisjointSets & operator=(const DisjointSets & other);

    /**
     * Creates n unconnected root nodes at the end of the vector.
     * 
     * @param num The number of nodes to create.
     * */
    void addelements(int num);

    /**
     * Find the root index of a given element.
     * This function should compress paths during 
     * tracking back of recursions.
     * 
     * @param elem The elem to find root of.
     * @return the index of the root of he pu-tree 
     * in which the parameter elem resides.
     * */
    int find(int elem);

    /**
     * Setunion for two sets using union-by-size.
     * 
     * That is, the smaller sets (in terms of number of nodes) 
     * should point at the larger one.
     * 
     * The arguments to setunion might not be the roots,
     * so this function should find the roots of the given parms.
     * If the two sets are the same size, make the second set 
     * point to the first set.
     * 
     * @param a Index of the first elements to union.
     * @param b Index of the second elements to union.
     * */
    void setunion(int a, int b);

    /**
     * Return the number of nodes in the up-tree 
     * containing the given elem.
     * 
     * @param elem 
     * @return the number of nodes in the up-tree 
     * containing the given elem
     * */
    int size(int elem);

    /**
     * Clear _elems
     * */
    void clearDSet();

    private:
    std::vector<int> _elems;
};