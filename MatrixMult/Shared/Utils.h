//
// Created by laursen86 on 2/17/16.
//

#ifndef INORDER_UTILS_H
#define INORDER_UTILS_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;

class Utils {

public:
    const static long min_size = 2; //10
    const static long max_size = pow(2,11); //10000000 //10^7
    const static long avg = 5; //10^5

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
    template<typename T>
    static void printArray(T *data, int size)
    {
        cout <<  "[";
        for( unsigned int i = 0; i < size; i++)
        {
            cout << data[i] << ",";
        }
        cout <<  "]" << endl;
    }

    template<typename T>
    static void printFancyMatrixArray(T *data, int row)
    {
        unsigned int size = row*row;
        const int width = 6;
        cout << endl;
        cout <<    "[";
        for( unsigned int i = 0, r = 1; i < size; i++, r = (i + 1) % row)
        {
            cout <<  setw(width) << data[i];

            if(!r){
                cout <<  "]" << endl;
                if(i + 1 < size) cout <<  "[";
            }
            else cout << ",";

        }
        cout << endl;
    }

};


#endif //INORDER_UTILS_H
