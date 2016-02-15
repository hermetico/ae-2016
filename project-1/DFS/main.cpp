#include <iostream>
#include <vector>
#include "DFSArray.h"
#include <papi.h>

using namespace std;

void handle_error(int error) {
    cout << error << endl;
}



void fillRandomData(vector<int> *data, int length, int init, int offset)
{
    int min_offset = 0, increase_offset;
    for(int i = 0, j = init; i < length; i++,j++)
    {
        increase_offset = min_offset + (rand() % (offset - 0 + 1));
        j += increase_offset;
        data->push_back(j);
    }
}

void fillRandomData(vector<int> *data,  int init, int offset)
{
    int min_offset = 0, increase_offset;
    for(int i = 0, j = init; i < data->size(); i++,j++)
    {
        increase_offset = min_offset + (rand() % (offset - 0 + 1));
        j += increase_offset;
        data[j];
    }
}

void testDFS()
{
    int k = 18, init = 1, offset = 10, key = 67;
    float alpha = .8;
    DFSArray *tree;
    vector<int> *data = new vector<int>;

    fillRandomData(data, k , init, offset);

    cout << "data size: " << data->size() << endl;
    cout << "data content: ";
    cout <<  "[";
    for( unsigned int i = 0; i < data->size(); i++)
    {
        cout << (*data)[i] << ",";
    }
    cout <<  "]" << endl;


    tree = new DFSArray(alpha);
    tree->fill(data);
    cout << "tree size: " << tree->length() << endl;
    cout << "tree content: " << endl;


    tree->printArray();
    cout << "predecessor of " << key << " : " << tree->predecessor(key) << endl;

    delete(tree);
    delete(data);
    return;
}



int main() {

    const long_long min_size = 10;
    const long_long max_size = 10000000;
    const long_long avg = 100000;

    const int init = 1, offset = 10;
    const float alpha = .5;
    DFSArray *tree;

    long_long result;
    clock_t begin_t, end_t;

    srand(time(0));
    tree = new DFSArray(alpha);

    for (long_long x = min_size; x <= max_size; x *= 1.1) {
        long_long s;
        vector<int> *data = new vector<int>(x);
        fillRandomData(data, init, offset);

        tree->fill(data);
        begin_t = clock();

        for (long_long j = 0; j < avg; j++) {
            s = 0 + (rand() % ((x * 4) - 0 + 1));

            result = tree->predecessor(s);
        }

        end_t = clock();

        double elapsed_secs = (double(end_t - begin_t) / CLOCKS_PER_SEC) / avg;

        cout << x << " " << elapsed_secs;

        cout << endl;

    }


    result = 42;

    return 0;
}