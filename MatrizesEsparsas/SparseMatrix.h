#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <iostream>
#include "Node.h"

class SparseMatrix {
    
    private:
    Node* m_head;

    public:

    SparseMatrix(int m, int n);

    ~SparseMatrix();

    void insert(int i, int j, double value);

    double get(int i, int j) {
        return 2;
    }

    void print();

};

#endif