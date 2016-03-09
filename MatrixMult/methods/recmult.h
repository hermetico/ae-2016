//
// Created by hermetico on 3/9/16.
//

#ifndef MATRIXMULT_RECMULT_H
#define MATRIXMULT_RECMULT_H

#include "imatrixmult.h"

class RecMult: public IMatrixMult{
public:
    RecMult(){};

    virtual void multiply(int n, int *A, int *B, int *C){
        int ax = 0, ay = 0, bx = 0, by = 0, size = n;

        // calls the recursive function
        recmult(A, B, C, ax, ay, bx, by, n, n);
    }

    void recmult(int *A, int *B, int *C, int ax, int ay, int bx, int by, int size, int n)
    {
        if(size == 1){
            C[ n * ax + by ] += A[ n * ax + ay ] * B[ n * bx + by ];
        }else{
            size /= 2;
            recmult(A, B, C, ax, ay, bx, by, size, n); // topleft * topleft
            recmult(A, B, C, ax, ay + size, bx + size, by, size, n); //topright *bottomleft

            recmult(A, B, C, ax + size, ay, bx, by, size, n); // bottomleft * topleft
            recmult(A, B, C, ax + size, ay + size, bx + size, by, size, n); //#bottomright * bottomleft

            recmult(A, B, C, ax, ay, bx, by + size, size, n); // topleft * topright
            recmult(A, B, C, ax, ay + size, bx + size, by + size, size, n); //#topright * bottomright

            recmult(A, B, C, ax + size, ay, bx, by + size, size, n); // bottomleft * topright
            recmult(A, B, C, ax + size, ay + size, bx + size, by + size, size, n); // bottomright * bottomright
        }
    }
};


#endif //MATRIXMULT_RECMULT_H
