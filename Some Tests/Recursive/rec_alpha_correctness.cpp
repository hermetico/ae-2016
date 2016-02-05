#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <climits>
using namespace std;


const int size = 100; //1 mil
const int maxval = 10000;//possible values range 0 to maxval
float alpha;


int pred(int query, int * arr, int length){ 
  
  int guess = length*alpha - 1;
  
  if (arr[guess] == query)
    return arr[guess];
      
  if(arr[guess]>query ){
    if(length*alpha <= 1)
      return -1;
    else
      return pred(query, arr, length*alpha-1);
  }
  else{
    if(length <= ceil(1/alpha)){//really ugly code in here to handle rare special cases. Something more elegant must exist. Works for everything I can think of trying.
      if (length==0)
	return -1;
      int bsf = INT_MIN;
      for(int i=0;i<length;i++){
	
	if (arr[guess+i]>bsf)
	  bsf = arr[guess+i];
	
      }
      return bsf;
    }
	
    if(arr[guess+1]>query)
      return arr[guess];

    return pred(query, &(arr[(guess+1)]), ceil(length*(1-alpha)));
  }
  
  
}

int main() {

  //srand(time(NULL)); seeding disabled for testing
  int* a = new int[size]; //make values
  for (int i=0; i<size; i++){
    a[i] = rand() % maxval;
      
  }
   std::sort(a, a+size);//sort them
   

   for (int i=0; i<size; i++){
     cout << i << ":  " << a[i] << endl;
   }
   
   
   int query;
   
   cout << "Random array has been generated and sorted."<<endl;
   

   //do binary search to find predecessor of 'query'
   int result;
   while(1){
     cout << "alpha: "<<endl;
     cin >> alpha;
     cout << "query: "<<endl;
     cin >> query;
     result = pred(query, a, size);
     if (result==-1)
       cout << query << " does not have a predecessor in this set." << endl;
     else
       cout << result << " is the predecessor of " << query <<endl;
   }
  return 0;
}
