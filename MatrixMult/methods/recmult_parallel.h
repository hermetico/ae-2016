//
// Created by hermetico on 3/9/16.
//

#ifndef MATRIXMULT_RECMULT_PARALLEL_H
#define MATRIXMULT_RECMULT_PARALLEL_H

#include "imatrixmult.h"


#include <omp.h>


class RecMultParallel: public IMatrixMult{

private:
    int threads = 1;
public:
    RecMultParallel(){};
    void setThreads(int t){threads = t;};

    virtual void multiply(int n, int *A, int *B, int *C){
        // calls the recursive function
        int size = n;
        int sub_size = size / 2;
        int b = sub_size, c = sub_size * size, d = sub_size * (size+1); // a = 0;

        if(threads == 1)
        {

            recmult(A, B, C, sub_size, size); // topleft * topleft -> topleft
            recmult(A + b, B + c, C, sub_size, size); //topright * bottomleft -> topleft

            recmult(A + c, B, C + c, sub_size, size); // bottomleft * topleft -> bottomleft
            recmult(A + d, B + c, C + c, sub_size, size); // bottomright * bottomleft -> bottomleft

            recmult(A, B + b, C + b, sub_size, size); // topleft * topright -> topright
            recmult(A + b, B + d, C + b, sub_size, size); //topright * bottomright -> topright

            recmult(A + c, B + b, C + d, sub_size, size); // bottomleft * topright -> bottomright
            recmult(A + d, B + d, C + d, sub_size, size); // bottomright * bottomright -> bottomright
        }
        else if(threads == 2) {
#pragma omp parallel sections
            {
#pragma omp section
                {
                    recmult(A, B, C, sub_size, size); // topleft * topleft -> topleft
                    recmult(A + b, B + c, C, sub_size, size); //topright * bottomleft -> topleft

                    recmult(A + c, B, C + c, sub_size, size); // bottomleft * topleft -> bottomleft
                    recmult(A + d, B + c, C + c, sub_size, size); // bottomright * bottomleft -> bottomleft
                }
#pragma omp section
                {
                    recmult(A, B + b, C + b, sub_size, size); // topleft * topright -> topright
                    recmult(A + b, B + d, C + b, sub_size, size); //topright * bottomright -> topright

                    recmult(A + c, B + b, C + d, sub_size, size); // bottomleft * topright -> bottomright
                    recmult(A + d, B + d, C + d, sub_size, size); // bottomright * bottomright -> bottomright
                }
            }

        }else if(threads == 4) {

#pragma omp parallel sections
            {
#pragma omp section
                {
                    recmult(A, B, C, sub_size, size); // topleft * topleft -> topleft
                    recmult(A + b, B + c, C, sub_size, size); //topright * bottomleft -> topleft
                }
#pragma omp section
                {
                    recmult(A + c, B, C + c, sub_size, size); // bottomleft * topleft -> bottomleft
                    recmult(A + d, B + c, C + c, sub_size, size); // bottomright * bottomleft -> bottomleft
                }
#pragma omp section
                {
                    recmult(A, B + b, C + b, sub_size, size); // topleft * topright -> topright
                    recmult(A + b, B + d, C + b, sub_size, size); //topright * bottomright -> topright
                }
#pragma omp section
                {
                    recmult(A + c, B + b, C + d, sub_size, size); // bottomleft * topright -> bottomright
                    recmult(A + d, B + d, C + d, sub_size, size); // bottomright * bottomright -> bottomright
                }
            }
        }else if(threads == 8) {

#pragma omp parallel sections
            {
#pragma omp section
                {
                    recmult(A, B, C, sub_size, size); // topleft * topleft -> topleft
                }
#pragma omp section
                {
                    recmult(A + b, B + c, C, sub_size, size); //topright * bottomleft -> topleft
                }
#pragma omp section
                {
                    recmult(A + c, B, C + c, sub_size, size); // bottomleft * topleft -> bottomleft
                }
#pragma omp section
                {
                    recmult(A + d, B + c, C + c, sub_size, size); // bottomright * bottomleft -> bottomleft
                }
#pragma omp section
                {
                    recmult(A, B + b, C + b, sub_size, size); // topleft * topright -> topright
                }
#pragma omp section
                {
                    recmult(A + b, B + d, C + b, sub_size, size); //topright * bottomright -> topright
                }

#pragma omp section
                {
                    recmult(A + c, B + b, C + d, sub_size, size); // bottomleft * topright -> bottomright
                }
#pragma omp section
                {
                    recmult(A + d, B + d, C + d, sub_size, size); // bottomright * bottomright -> bottomright
                }
            }
        }



    }

    void recmult(int *A, int *B, int *C,  int sub_size, int size)
    {
        if(sub_size == 1){
            #pragma omp critical
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


#endif //MATRIXMULT_RECMULT_PARALLEL_H
