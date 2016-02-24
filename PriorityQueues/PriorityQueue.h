
#ifndef PRIORITYQUEUE_PRIORITYQUEUES_H
#define PRIORITYQUEUE_PRIORITYQUEUES_H

#include <vector>

using namespace std;

template <class Value>
class PriorityQueue {

protected:
    vector<Value> _heap;

public:
    virtual void Insert(Value v) = 0;
    virtual Value DeleteMin() = 0;

};


#endif //PRIORITYQUEUE_PRIORITYQUEUES_H
