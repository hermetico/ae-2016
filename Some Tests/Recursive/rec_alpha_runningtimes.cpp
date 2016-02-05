#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <math.h>

using namespace std;
const int size = 1000000; //1 mil
const int avg = 1000000; // 1 mil
const int maxval = 1000000;//possible values range 0 to maxval
float alpha;



int pred(int query, int * arr, int length){

  
  int guess = (length)*alpha-1;
  
  if (arr[guess] == query)
    return arr[guess];
      
  if(arr[guess]>query ){
    if(length*alpha <= 1)
      return -1;
    else
      return pred(query, arr, length*alpha-1);
  }
  else{ //arr[guess]<query
    if(length <= 1)
      return arr[guess];
	
    if(arr[guess+1]>query)
      return arr[guess];

    return pred(query, &(arr[(guess+1)]), ceil(length*(1-alpha)));
  }
  
  
}

int main() {
 
   int query;
      
   std::clock_t start, stop;

   

       
   
   for(float alp=0.03; alp<1; alp+=0.01){


     
     alpha = alp; //set global var


     int* a = new int[size]; //make values //wtf is going on here  
     for (int k=0; k<size; k++){
       a[k] = rand() % maxval;
       
     }
   

     std::sort(a, a+size);//sort them  

     
     start = clock();
     for(int j=0; j<avg; j++){
       query = rand() % maxval;
       pred(query, a, size);
       
     }
   
     stop = clock();

     cout << alp << " " << (stop - start) / (double(CLOCKS_PER_SEC)) << std::endl;

       
   }
   
   return 0;
}
