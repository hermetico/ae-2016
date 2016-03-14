//
// Created by hermetico on 3/9/16.
//

#ifndef MATRIXMULT_RECMULT_H
#define MATRIXMULT_RECMULT_H

#include "imatrixmult.h"
using namespace std;

class RecMult: public IMatrixMult{

private:
    int perform_simple_mult_at_level = 0; //0 doesn't perform optimization

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

    void simple_mult_extended(int *A, int *B, int *C,  int sub_m, int sub_n, int sub_p, int m, int n, int p)
    {

        for(int i = 0; i < sub_m; i++)
        {
            for(int j = 0; j < sub_n; j++)
            {
                for(int k = 0; k < sub_p; k++)
                {
                    C[i * p + j] += A[i * n + k] * B[ k * p + j];
                }
            }
        }
    }

    int max(int a, int b){
        return a > b ? a : b;
    }

public:
    RecMult(){};
    void set_limit(int limit){perform_simple_mult_at_level=limit;}

    virtual void multiply(int n, int *A, int *B, int *C){
        // calls the recursive function
        //recmult(A, B, C, n, n);
        recmult_extended(A, B, C, n, n, n, n, n, n);
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

    void recmult_extended(int *A, int *B, int *C,  int sub_m, int sub_n, int sub_p, int m, int n, int p)
    {

        if( perform_simple_mult_at_level && perform_simple_mult_at_level >= max(sub_m, max(sub_n, sub_p)) )
        {

            simple_mult_extended(A, B, C, sub_m, sub_n, sub_p, m, n, p);
        }else if(sub_m == 1 && sub_n ==1 && sub_p == 1) {
            C[0] += A[0] * B[0];
        }
        else if( sub_m >= max(sub_n, sub_p))
        {

            /* we split the range of m
             * |C1| |A1|       |A1B|
             * |  |=|  | * B = |   |
             * |C2| |A2|       |A2B|
             *
             */

            int sub_m1 = sub_m/2;
            int sub_m2 = sub_m - sub_m1;
            int offset_a2 = sub_m1 * n; // n is the size of the row in a
            int offset_c2 = sub_m1 * p; // p is the size of the row in c

            recmult_extended(A, B, C, sub_m1, sub_n, sub_p, m, n, p); // c1 <- A1 * B
            recmult_extended(A + offset_a2, B, C + offset_c2, sub_m2, sub_n, sub_p, m, n, p); // c2 <- A2 * B
        }
        else if( sub_n >= max(sub_m, sub_p))
        {
            /* we split the range of n
             *                |B1|
             * C = |A1  A2| * |  | = A1B1 + A2B2
             *                |B2|
             */

            int sub_n1 = sub_n/2;
            int sub_n2 = sub_n - sub_n1;
            int offset_a2 = sub_n1;
            int offset_b2 = sub_n1 * p; // p is the size of the row in b

            recmult_extended(A, B, C, sub_m, sub_n1, sub_p, m, n, p); //c <- A1 * B1
            recmult_extended(A + offset_a2, B + offset_b2, C, sub_m, sub_n2, sub_p, m, n, p); //c <- A2 * B2

        }
        else if( sub_p >= max(sub_m, sub_n))
        {
            /* we split the range of p
             *
             * |C1 C2| = A * |B1  B1| = |AB1  AB2|
             *
             */

            int sub_p1 = sub_p/2;
            int sub_p2 = sub_p - sub_p1;
            int offset_c2 = sub_p1;
            int offset_b2 = sub_p1;

            recmult_extended(A, B, C, sub_m, sub_n, sub_p1, m, n, p); //c1 <- A * B1
            recmult_extended(A, B + offset_b2, C + offset_c2, sub_m, sub_n, sub_p2, m, n, p); //c2 <- A * B2


        }
    }
};


#endif //MATRIXMULT_RECMULT_H
