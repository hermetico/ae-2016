#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>

using namespace std;

//for convenience assume quadratic, and s divides n (paper)

void tiledmult (int n, int* A, int* B, int* C){
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

int main() {
    int n=6; //length of quadratic matrix
    int nsq = n*n;
    int A[36]={0}; // <-- make dynamical. Should be able to put the variable nsq in there and allocate on runtime
    int B[36]={0};
    int C[36]={0};




    for(int i=0;i<nsq;i++){
        A[i] = i;
        B[i] = i*2;//just example matrices to test on
        A[i] = 1;
        B[i] = 1;
        A[i] = i;
        B[i] = nsq-i*2;
        A[i] = i;
        B[i] = nsq+i;
    }
    tiledmult(n, A,B,C);

    for(int i=0;i<nsq;i++){
        cout << C[i] << "\t";
        cout << endl;
    }
    cout << endl << C[11] << endl;


    //if we want it to take any matrix, one can increase n until s divides it, and then add zeros until they are square (or do annoying special cases code)
}
void recmult(){}//recmult time