//
// Created by laursen86 on 2/17/16.
//

#ifndef INORDER_INORDERSEARCH_H
#define INORDER_INORDERSEARCH_H

#include <vector>

using namespace std;

class InOrder {

private:
    vector<long> _data;
    float _alpha;


public:
    InOrder(vector<long> &data, float alpha) {
        _data = data;
        _alpha = alpha;
    }

    ~InOrder() {
        _data.clear();
    }

    long Predecessor(long x) {
        long res = -1;
        long min = 0;
        long max = _data.size();

        while (max >= min)
        {
            int pointer =  min + (max-min)*_alpha;

            if(_data[pointer] ==  x)
                return x;

            else if(_data[pointer] < x) // move pointer to the right
            {
                // if new value is higher than previous result, it's a better choice
                if(_data[pointer] > res)
                    res = _data[pointer];

                min = pointer + 1;
            }
            else if(_data[pointer] > x) // move pointer to the left
            {
                max = pointer - 1;
            }
        }

        return res;
    }

};


#endif //INORDER_INORDERSEARCH_H
