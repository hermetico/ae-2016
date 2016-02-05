//
// Created by ballololz on 03-Feb-16.
//

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
int leftbranches = 0;
int rightbranches = 0;

struct BRANCHINGS{
	int left;
	int right;	
};

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
BRANCHINGS binary_search_branchings(vector<int> *data, int search, float alpha){
	
	BRANCHINGS res;
	res.left = 0;
	res.right = 0;
    int min = 0, max = data->size();

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
        if((*data)[pointer] ==  search) return res;

        else if((*data)[pointer] < search) // move pointer to the right
        {
			res.right++;

            min = pointer + 1;
        }
        else if((*data)[pointer] > search) // move pointer to the left
        {
			res.left++;
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
    const long size = 1000000; //1 mil
    const long avg = 1000000; //1 mil
	
    int  s;
	BRANCHINGS res;
    // random seed
    srand(time(0));
	int left_total;
	int right_total;



    for (float alp=0.03; alp<1; alp+=0.01)
    {

        fill(size, &data);
		left_total = 0;
		right_total = 0;	

        // test avg times to make an average
        for (int j = 0; j < avg; j++) {
            //show_data(&data);
            s = 0 + (rand() % ((size * 4) - 0 + 1));
            res = binary_search_branchings(&data, s, alp);
			left_total += res.left;
			right_total += res.right;
        }
		float dont_round_please;
		dont_round_please = (float)left_total/avg;
        cout << alp << " " << dont_round_please << " ";
		dont_round_please = (float)right_total/avg;
		cout << dont_round_please << endl;// << " search: " << s << " pred: " << res << endl;
        // clock end



        data.clear();
    }

    return 0;
};
