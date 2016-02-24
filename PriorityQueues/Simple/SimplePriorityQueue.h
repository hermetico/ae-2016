#ifndef PRIORITYQUEUES_SIMPLEPRIORITYQUEUE_H
#define PRIORITYQUEUES_SIMPLEPRIORITYQUEUE_H

#include "../IPriorityQueue.h"

template <class Value>
class SimplePriorityQueue: public IPriorityQueue<Value> {

private:
    vector<Value> _heap = vector<Value>();
public:
    virtual void Insert(Value v) {
        _heap.push_back(v);

    }
    virtual Value DeleteMin() {
        Value ret = _heap.front();
        _heap.erase(_heap.begin());

        return ret;

    }
};


#endif //PRIORITYQUEUES_SIMPLEPRIORITYQUEUE_H
