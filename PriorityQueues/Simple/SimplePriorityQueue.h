#ifndef PRIORITYQUEUES_SIMPLEPRIORITYQUEUE_H
#define PRIORITYQUEUES_SIMPLEPRIORITYQUEUE_H

#include "../PriorityQueue.h"

template <class Value>
class SimplePriorityQueue: public PriorityQueue {

public:
    virtual void Insert(Value v);
    virtual Value DeleteMin();
};


#endif //PRIORITYQUEUES_SIMPLEPRIORITYQUEUE_H
