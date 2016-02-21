//
// Created by laursen86 on 2/17/16.
//

#ifndef BFS_BFS_H
#define BFS_BFS_H

#include <vector>

using namespace std;

class BFS {

private:
    vector<long> _bfsTree;

    void BuildBFSTreeRecursive(vector<long> &bfs, long min, long max, long index, vector<long> &sortedArray) {

        long size = max-min+1;
        long pointerIndex = min + size*0.5;

        bfs[index] = sortedArray[pointerIndex];

        if(size > 1) {
            BuildBFSTreeRecursive(bfs, min, pointerIndex - 1, 2 * index + 1, sortedArray);
            BuildBFSTreeRecursive(bfs, pointerIndex + 1, max, 2 * index + 2, sortedArray);
        }

    }

    void BuildBFSTree(vector<long> &sortedArray) {
        _bfsTree = vector<long>(sortedArray.size()*2, 0);
        BuildBFSTreeRecursive(_bfsTree, 0, sortedArray.size()-1, 0, sortedArray);
    }

    long BFSSearchRecursive(long query, long index) {
        long result = -1;

        if(index >= _bfsTree.size()) {
            return -1;
        }

        if(query < _bfsTree[index]) {
            result = BFSSearchRecursive(query, 2*index+1);
        } else if(query > _bfsTree[index]) {
            result = BFSSearchRecursive(query, 2*index+2);
        }

        if(result == -1) {
            result = _bfsTree[index];
        }

        return result;
    }

public:
    BFS(vector<long> &data) {
        BuildBFSTree(data);
    }

    ~BFS() {
        _bfsTree.clear();
    }

    long Predecessor(long x) {
        long i = 0;
        long result = -1;

        while(i < _bfsTree.size()) {

            if(x < _bfsTree[i]) {
                i = 2*i+1;
            } else if(x > _bfsTree[i]) {
                result = _bfsTree[i];
                i = 2*i+2;
            } else {
                return x;
            }

        }

        return result;
    }

    long PredecessorRecursive(long x) {
        BFSSearchRecursive(x, 0);
    }
};



#endif //BFS_BFS_H
