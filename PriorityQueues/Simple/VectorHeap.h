#ifndef PRIORITYQUEUES_VECTORHEAP_H
#define PRIORITYQUEUES_VECTORHEAP_H

#include "../IPriorityQueue.h"

template <class Value>
class VectorHeap: public IPriorityQueue<Value> {

private:
    vector<Value> _vector;

    void BubbleDown(long index) {
        long length = _vector.size();
        long leftChildIndex = 2*index+1;
        long rightChildIndex = 2*index+2;

        if(leftChildIndex >= length)
            return; //Its a leaf

        long minIndex = index;

        if(_vector[index] > _vector[leftChildIndex])
            minIndex = leftChildIndex;

        if(rightChildIndex < length && _vector[minIndex] > _vector[rightChildIndex])
            minIndex = rightChildIndex;

        if(index != minIndex) {
            SwapElements(index, minIndex);
            BubbleDown(minIndex);
        }
    }

    void BubbleUp(long index) {
        if(index == 0)
            return; //At root

        long parentIndex = (index-1)/2;

        if(_vector[parentIndex] > _vector[index]) {
            SwapElements(parentIndex, index);
            BubbleUp(parentIndex);
        }
    }

    void SwapElements(long index1, long index2) {
        Value temp = _vector[index1];
        _vector[index1] = _vector[index2];
        _vector[index2] = temp;
    }

public:

    VectorHeap(long size) : _vector(size) {}

    virtual void Insert(Value v) {
        long length = _vector.size();
        _vector.push_back(v);
        BubbleUp(length);
    }

    Value GetMin() {
        return _vector[0];
    }

    virtual Value DeleteMin() {
        Value minValue = GetMin();

        long length = _vector.size();

        if(length == 0)
            return minValue;

        _vector[0] = _vector[length-1];
        _vector.pop_back();
        BubbleDown(0);

        return minValue;

    }
};

#endif //PRIORITYQUEUES_VECTORHEAP_H
