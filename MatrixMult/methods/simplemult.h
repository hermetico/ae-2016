//
// Created by hermetico on 3/10/16.
//

#ifndef MATRIXMULT_SIMPLE_H
#define MATRIXMULT_SIMPLE_H

#include "imatrixmult.h"

class SimpleMult: public IMatrixMult{
public:
    SimpleMult(){};

    virtual void multiply(int n, int *A, int *B, int *C){

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                for(int k = 0; k < n; k++)
                {
                    C[i * n + j] += A[i * n + k] * B[ k * n + j];
                }
            }
        }
    }
};

#endif //MATRIXMULT_SIMPLE_H
