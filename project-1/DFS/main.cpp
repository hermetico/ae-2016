#include <iostream>
#include <vector>
#include "DFSArray.h"
using namespace std;

void fillRandomData(vector<int> *data, int length, int init, int offset)
{
    int min_offset = 0, increase_offset;
    for(int i = 0, j = 1; i < length; i++,j++)
    {
        increase_offset = min_offset + (rand() % (offset - 0 + 1));
        j += increase_offset;
        data->push_back(j);
    }
}



int main() {

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
    return 0;
}