#include <iostream>

#ifndef MATRIXMULT_TILEDMULT_H
#define MATRIXMULT_TILEDMULT_H

#include "imatrixmult.h"
using namespace std;


class TiledMult: public IMatrixMult {

public:
    TiledMult(){};

    virtual void multiply(int n, int *A, int *B, int *C)
    {
        int s = 3; //this parameter we must tune. S must divide n!
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
