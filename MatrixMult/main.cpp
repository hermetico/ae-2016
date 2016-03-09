#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <time.h>
#include <stdlib.h>


#include "methods/imatrixmult.h"
#include "methods/tiledmult.h"
#include "methods/recmult.h"
#include "Shared/Utils.h"
#define MAX_NUM_ALLOWED 10;


using namespace std;


//for convenience assume quadratic, and s divides n (paper)

void _tiledmult (int n, int* A, int* B, int* C){
    int s = 3; //this parameter we must tune. S must divide n!
    for (int i=0;i<n/s;i++){
        for (int j=0;j<n/s;j++){
            for (int k=0;k<n/s;k++){
                //ordmult. mult two s by s matrices
                //its still n^3 cuz the above does (n/s)^3 steps and below does s^3. so its n^3 / s^3 * s^3 = n^3
                for(int ii=0;ii<s;ii++){
                    for (int jj=0;jj<s;jj++){
                        for (int kk=0;kk<s;kk++){
                            //C[i*s+ii, j*s+jj] means (i*s+ii)*n + j*s+jj

                            C[(i*s+ii)*n+j*s+jj] += A[(i*s+ii)*n+k*s+kk] * B[(k*s+kk)*n+j*s+jj];
                        }
                    }
                }
            }
        }
    }
}

/*
 * Fills one matrx
 */
void fillMatrix(int n, int* M)
{
    int size = n*n;
    for(unsigned int i=0;i<size;i++)
    {
        M[i] = rand() % MAX_NUM_ALLOWED;
    }
}

void fillZeros(int n, int* M)
{
    int size = n*n;
    for(unsigned int i=0;i<size;i++)
    {
        M[i] = 0;
    }
}


int main() {
    srand(time(NULL));

    int n=2; //length of quadratic matrix
    int nsq = n*n;

    int *A = (int *) malloc(sizeof(int) * nsq);
    int *B = (int *) malloc(sizeof(int) * nsq);
    int *C = (int *) malloc(sizeof(int) * nsq);


    // one method
    TiledMult tiledmult = TiledMult();
    RecMult recmult = RecMult();
    IMatrixMult *method = &recmult;



    // fill matrix with random values
    fillMatrix(n, A);
    fillMatrix(n, B);
    fillZeros(n, C);
    Utils::printFancyMatrixArray<int>(A, n);
    Utils::printFancyMatrixArray<int>(B, n);


    //DELETEME
    clock_t begin = clock();

    method->multiply(n, A,B,C);

    //DELETEME
    clock_t end = clock();

    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Elapsed time for n: " << n << " : " << elapsed_secs << "s "<< endl;

    Utils::printFancyMatrixArray<int>(C, n);


    //if we want it to take any matrix, one can increase n until s divides it, and then add zeros until they are square (or do annoying special cases code)
}
void recmult(){}//recmult time