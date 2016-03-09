#ifndef MATRIXMULT_MATRIXMULT_H
#define MATRIXMULT_MATRIXMULT_H




class IMatrixMult {

public:
    virtual void multiply (int n, int* A, int* B, int* C) = 0;

};

#endif //MATRIXMULT_MATRIXMULT_H
