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
#include "methods/simplemult.h"
#include "Shared/Utils.h"
#define MAX_NUM_ALLOWED 100;


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
 * Fills one matrix
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

// test to check the implememtations
void benchmark(int test){

    int n=8; //length of quadratic matrix
    int nsq = n*n;

    int *A = (int *) malloc(sizeof(int) * nsq);
    int *B = (int *) malloc(sizeof(int) * nsq);
    int *C = (int *) malloc(sizeof(int) * nsq);



    // one method
    IMatrixMult *method;


    // fill matrix with random values
    fillMatrix(n, A);
    fillMatrix(n, B);
    fillZeros(n, C);

    Utils::printFancyMatrixArray<int>(A, n);
    Utils::printFancyMatrixArray<int>(B, n);


    // select method
    switch(test){
        case 0: {

            SimpleMult simplemult = SimpleMult();
            simplemult.multiply(n, A,B,C);
            break;
        }
        case 1:
        {
            TiledMult tiledmult = TiledMult();
            tiledmult.multiply(n, A,B,C);
            break;
        }
        case 2: {

            RecMult recmult = RecMult();
            recmult.multiply(n, A,B,C);
            break;
        }

    }

    Utils::printFancyMatrixArray<int>(C, n);
    /// free
    free(A);
    free(B);
    free(C);

}

void implementation_test(IMatrixMult *method){
    int n=8; //length of quadratic matrix
    int nsq = n*n;

    int *A = (int *) malloc(sizeof(int) * nsq);
    int *B = (int *) malloc(sizeof(int) * nsq);
    int *C = (int *) malloc(sizeof(int) * nsq);


    // fill matrix with random values
    fillMatrix(n, A);
    fillMatrix(n, B);
    fillZeros(n, C);

    Utils::printFancyMatrixArray<int>(A, n);
    Utils::printFancyMatrixArray<int>(B, n);


    method ->multiply(n, A,B,C);

    Utils::printFancyMatrixArray<int>(C, n);
    /// free
    free(A);
    free(B);
    free(C);
}



int main(int argc, char **argv) {
    srand(time(NULL));

    int run_type =  atoi(argv[1]);
    int method_type =  atoi(argv[2]);


    switch(run_type){
        case 0:
            switch(method_type){
                case 0: {

                    SimpleMult simplemult = SimpleMult();
                    implementation_test(&simplemult);
                    break;
                }
                case 1:
                {
                    TiledMult tiledmult = TiledMult();
                    implementation_test(&tiledmult);
                    break;
                }
                case 2: {

                    RecMult recmult = RecMult();
                    implementation_test(&recmult);
                    break;
                }
            }
            break;
        case 1:
            benchmark(method_type);
            break;
    }

    //if we want it to take any matrix, one can increase n until s divides it, and then add zeros until they are square (or do annoying special cases code)
}