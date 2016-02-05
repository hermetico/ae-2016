#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iterator>

using namespace std;

const int N=100;
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

  //srand(time(NULL)); seeding disabled for testing
  int* a = new int[N]; //make values
  for (int i=0; i<N; i++){
    a[i] = rand() % maxval;
      
  }
   std::sort(a, a+N);//sort them
   

   for (int i=0; i<N; i++){
     cout << i << ":  " << a[i] << endl;
   }
   
   
   int query;
   
   cout << "Random array has been generated and sorted. Please enter your query: "<<endl;
   

   //do binary search to find predecessor of 'query'
   int result;
   while(1){
     cin >> query;
     result = pred(query, a, N);
     if (result==-1)
       cout << query << " does not have a predecessor in this set." << endl;
     else
       cout << result << " is the predecessor of " << query <<endl;
   }
  return 0;
}
