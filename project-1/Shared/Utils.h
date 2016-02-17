//
// Created by laursen86 on 2/17/16.
//

#ifndef INORDER_UTILS_H
#define INORDER_UTILS_H
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class Utils {


public:
    static const long min_size = 10;
    static const long max_size = pow(10, 7);
    static const long avg = pow(10, 5);

    static void FillRandomData(vector<long> &data,  int init, int offset) {
        long increase_offset = 0;
        for(long i = 0, j = init; i < data.size(); i++,j++)
        {
            increase_offset += rand() % offset + 1;
            data[i] = increase_offset;
        }
    }





};


#endif //INORDER_UTILS_H
