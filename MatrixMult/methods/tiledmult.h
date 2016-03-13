#include <iostream>

#ifndef MATRIXMULT_TILEDMULT_H
#define MATRIXMULT_TILEDMULT_H

#include "imatrixmult.h"


class TiledMult: public IMatrixMult {

public:
    TiledMult(){};

    virtual void multiply(int n, int *A, int *B, int *C)
    {
        int s = 14;
        //this parameter we must tune. S must divide n!

        /*if (n >= 2) s = 2;
        if (n >= 4) s = 4;
        if (n >= 8) s = 8;
        if (n >= 16) s = 16;
        //if (n >= 32) s = 32;
        //if (n >= 64) s = 64;
        //if (n >= 128) s = 128;
        //if (n >= 256) s = 256;
        */
        while( n%--s != 0);

        for (int i = 0; i < n / s; i++)
        {
            for (int j = 0; j < n / s; j++)
            {
                for (int k = 0; k < n / s; k++)
                {
                    //ordmult. mult two s by s matrices
                    //its still n^3 cuz the above does (n/s)^3 steps and below does s^3. so its n^3 / s^3 * s^3 = n^3
                    for (int ii = 0; ii < s; ii++)
                    {
                        for (int jj = 0; jj < s; jj++)
                        {
                            for (int kk = 0; kk < s; kk++)
                            {
                                //C[i*s+ii, j*s+jj] means (i*s+ii)*n + j*s+jj

                                C[(i * s + ii) * n + j * s + jj] +=
                                        A[(i * s + ii) * n + k * s + kk] * B[(k * s + kk) * n + j * s + jj];
                            }
                        }
                    }
                }
            }
        }

    }
};

#endif //MATRIXMULT_TILEDMULT_H
