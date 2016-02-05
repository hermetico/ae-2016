#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <math.h>

using namespace std;
const int MAXN = 1000000;
const int N=100;
const int iter = 100000000;
const int maxval = 10000;

int pred(int query, int * arr, int length){ 
  
  int guess = (length+1)/2 -1;
  
  if (arr[guess] == query)
    return arr[guess];
      
  if(arr[guess]>query ){
    if(length==2)
      return -1;
    else
      return pred(query, arr, (length-1)/2);
  }
  if(arr[guess]<query){
    if(length == 1)
      return arr[guess];
	
    if(arr[guess+1]>query)
      return arr[guess];

    return pred(query, &(arr[(guess+1)]), length/2);
  }
  
  
}

int main() {
 
   int query;
      
   std::clock_t start, stop;

   for(int i=1000; i<MAXN; i=floor(i*1.3)){

     srand(time(NULL));
     int* a = new int[N]; //make values
     for (int k=0; k<N; k++){
       a[k] = rand() % maxval;
       
     }
   std::sort(a, a+N);//sort them

     
   start = std::clock();
   for(int j=0; j<iter; j++){
     
       query = rand() % maxval;
       pred(query, a, N);
       
     }
   
     stop = std::clock();

     cout << i << "\t" << stop - start / (double(CLOCKS_PER_SEC)) << "\n" << std::endl; 

       // first output is human-readable, second one is convenient for data
   }
   
   return 0;
}
