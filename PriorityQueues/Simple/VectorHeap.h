#ifndef PRIORITYQUEUES_VECTORHEAP_H
#define PRIORITYQUEUES_VECTORHEAP_H


#include "../IPriorityQueue.h"

template <class Key, class Value>
struct ElementStruct {Key key; Value value;};

template <class Key, class Value>
class VectorHeap: public IPriorityQueue<Value> {

    typedef ElementStruct<Key, Value> Element;

private:
    Element *_array;
    long _size = 0;

    void BubbleDown(long index) {
        long leftChildIndex = 2*index+1;
        long rightChildIndex = 2*index+2;

        if(leftChildIndex >= _size)
            return; //Its a leaf

        long minIndex = index;

        if(_array[index].key > _array[leftChildIndex].key)
            minIndex = leftChildIndex;

        if(rightChildIndex < _size && _array[minIndex].key > _array[rightChildIndex].key)
            minIndex = rightChildIndex;

        if(index != minIndex) {
            swap(_array[index], _array[minIndex]);
            BubbleDown(minIndex);
        }
    }

    void BubbleUp(long index) {
        if(index == 0)
            return; //At root

        long parentIndex = (index-1)/2;

        if(_array[parentIndex].key > _array[index].key) {
            swap(_array[parentIndex], _array[index]);
            BubbleUp(parentIndex);
        }
    }

public:

    VectorHeap(long size) {
        _array = new Element[size];
    }

    ~VectorHeap() {
        delete[] _array;
    }

    virtual void Insert(Value v) {
        _array[_size].key = v;
        _array[_size].value = v;
        BubbleUp(_size);
        _size++;
    }

    Element GetMin() {
        return _array[0];
    }

    virtual Value DeleteMin() {
        Element minValue = GetMin();

        if(_size == 0)
            return minValue.key;

        _array[0] = _array[_size - 1];
        _size--;
        BubbleDown(0);

        return minValue.value;

    }
};

#endif //PRIORITYQUEUES_VECTORHEAP_H
