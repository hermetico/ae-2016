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
    vector<int> tree;
    int depth;
    int possible_response;
    bool bottom_reached;
    void fillArrayRecursive(vector<int> *data, int init, int end, int v, unsigned int index);
    void predecessorRecursive(int key,  unsigned int index, int size);



public:
    ~DFSArray();
    DFSArray();
    DFSArray(float alpha);
    DFSArray(vector<int> *data);
    DFSArray(vector<int> *data, float alpha);
    void fill(vector<int> *data);
    void printArray();
    void setAlpha(float alpha);
    int length();
    int predecessor(int key);
    void setVerboseMode(bool set);

};


#endif //ASSIGNMENT_TREEARRAY_H
