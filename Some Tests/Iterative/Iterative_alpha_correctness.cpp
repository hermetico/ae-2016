//
// Created by ballololz on 03-Feb-16.
//

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

/**
 * Dummy function which creates an array of non consecutive numbers, but sorted
 */
void fill(int k, vector<int> *data)
{
    int offset, min_offset = 0, max_offset = 5;

    for(int i = 0, j = 0; i < k; i++,j++)
    {
        offset = min_offset + (rand() % (max_offset - 0 + 1));
        j += offset;
        data->push_back(j);
    }
}

/**
 * binary search with custom alpha to skew the tree
 */
int binary_search(vector<int> *data, int search, float alpha){
    int res = -1, min = 0, max = data->size();

    while (max >= min)
    {
        // alpha = 0.5
        int pointer =  min + (max-min) *alpha;
        /*
        cout << "min: " << min << endl;
        cout << "max: " << max << endl;
        cout << "pointer: " << pointer << endl;
        cout << "current: " << (*data)[pointer] << endl;
        */
        if((*data)[pointer] ==  search) return search;

        else if((*data)[pointer] < search) // move pointer to the right
        {
            // if new value is higher than previous result, it's a better choice
            if((*data)[pointer] > res ) res = (*data)[pointer];

            min = pointer + 1;
        }
        else if((*data)[pointer] > search) // move pointer to the left
        {
            max = pointer - 1;
        }

    }
    return res;
}

void show_data(vector<int> *data)
{
    for( int i = 0; i < data->size(); i++)
    {
        cout << (*data)[i] << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> data;
    const long size = 100;

    clock_t begin_t, end_t;
    double elapsed_secs;

    int  s, res;
    // random seed
    srand(time(0));



   
    fill(size, &data);
    
    // test avg times to make an average
    float alpha;
    int query;
    show_data(&data);
    while (1) {
      cout << "input alpha " << endl;
      cin >> alpha;
      cout << "input query " << endl;
      cin >> query;
      res = binary_search(&data, query, alpha);
      
      if (res < 0)
	cout << query << " does not have a predecessor in the set." << endl;
      else
	cout << "predecessor of " << query << " is " << res << endl;
	  
	  
    }

    return 0;
};
