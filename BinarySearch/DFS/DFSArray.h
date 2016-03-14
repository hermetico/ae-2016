//
// Created by hermetico on 2/13/16.
//

#ifndef ASSIGNMENT_TREEARRAY_H
#define ASSIGNMENT_TREEARRAY_H


#include <vector>
#include <cstdlib>
using namespace std;

class DFSArray {
private:
    bool verbose;
    float alpha;
    vector<long> tree;
    int depth;
    int possible_response;
    bool bottom_reached;
    void fillArrayRecursive(vector<long> *data, int init, int end, int v, unsigned int index);
    void predecessorRecursive(long key,  unsigned int index, int size);



public:
    ~DFSArray();
    DFSArray();
    DFSArray(float alpha);
    DFSArray(vector<long> *data);
    DFSArray(vector<long> *data, float alpha);
    void fill(vector<long> *data);
    void printArray();
    void setAlpha(float alpha);
    int length();
    long predecessor(long key);

};


#endif //ASSIGNMENT_TREEARRAY_H
