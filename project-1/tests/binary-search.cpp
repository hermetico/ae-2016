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
        int pointer =  min + (max-min) /2;
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
    const long min_size = 1000;
    const long max_size = 1000000;
    const long avg = 100000;
    clock_t begin_t, end_t;
    double elapsed_secs;

    int  s,  alpha = 0.5, res;
    // random seed
    srand(time(0));



    for (int x = min_size; x < max_size; x += 1000)
    {

        fill(x, &data);
        begin_t = clock();

        // test avg times to make an average
        for (int j = 0; j < avg; j++) {
            //show_data(&data);
            s = 0 + (rand() % ((x * 4) - 0 + 1));
            res = binary_search(&data, s, alpha);
        }
        end_t = clock();
        double elapsed_secs = (double(end_t - begin_t) / CLOCKS_PER_SEC) / avg;
        cout << x << " " << elapsed_secs << endl;// << " search: " << s << " pred: " << res << endl;
        // clock end



        data.clear();
    }

    return 0;
};
