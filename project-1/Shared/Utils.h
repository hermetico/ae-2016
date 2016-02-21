//
// Created by laursen86 on 2/17/16.
//

#ifndef INORDER_UTILS_H
#define INORDER_UTILS_H
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Utils {

public:
    const static long min_size = 10;
    const static long max_size = 10000000; //10^7
    const static long avg = 10000; //10^5
    const static long step_size  = 1.1;

    static void FillRandomData(vector<long> &data,  int init, int offset) {
        long increase_offset = 0;
        for(long i = 0, j = init; i < data.size(); i++,j++)
        {
            increase_offset += rand() % offset + 1;
            data[i] = increase_offset;
        }
    }

    static void printVector(vector<long> *data)
    {
        cout <<  "[";
        for( unsigned int i = 0; i < data->size(); i++)
        {
            cout << (*data)[i] << ",";
        }
        cout <<  "]" << endl;
    }

};


#endif //INORDER_UTILS_H
