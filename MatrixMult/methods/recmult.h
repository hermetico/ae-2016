//
// Created by hermetico on 3/9/16.
//

#ifndef MATRIXMULT_RECMULT_H
#define MATRIXMULT_RECMULT_H

#include "imatrixmult.h"

class RecMult: public IMatrixMult{
private:
    int perform_simple_mult_at_level = 0;

    void simple_mult(int n, int *A, int *B, int *C){

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

public:
    RecMult(){};

    virtual void multiply(int n, int *A, int *B, int *C){
        // calls the recursive function
        recmult(A, B, C, n, n);
    }

    void recmult(int *A, int *B, int *C,  int sub_size, int size)
    {
        // if perform_simple_mult_at_level, avoid overhead using a simple mult
        // the value perform... should be tuned to fit the rest of the matrix in the cache
        if(perform_simple_mult_at_level && perform_simple_mult_at_level == sub_size)
        {
            simple_mult(sub_size, A, B, C);
        }
        else if(sub_size == 1){
            C[0] += A[0] * B[0];
        }else{

            /* Sub matrices first index positions
             * |A|B|
             * |C|D|
             */
            sub_size /= 2;
            int b = sub_size, c = sub_size * size, d = sub_size * (size+1); // a = 0;

            recmult(A, B, C, sub_size, size); // topleft * topleft -> topleft
            recmult(A + b, B + c, C, sub_size, size); //topright * bottomleft -> topleft

            recmult(A + c, B, C + c, sub_size, size); // bottomleft * topleft -> bottomleft
            recmult(A + d, B + c, C + c, sub_size, size); // bottomright * bottomleft -> bottomleft

            recmult(A, B + b, C + b, sub_size, size); // topleft * topright -> topright
            recmult(A + b, B + d, C + b, sub_size, size); //topright * bottomright -> topright

            recmult(A + c, B + b, C + d, sub_size, size); // bottomleft * topright -> bottomright
            recmult(A + d, B + d, C + d, sub_size, size); // bottomright * bottomright -> bottomright
        }
    }
};


#endif //MATRIXMULT_RECMULT_H
