//
// Created by Kim Laursen on 24/02/16.
//

#include "../PriorityQueue.h"

#ifndef PRIORITYQUEUES_SIMPLEPRIORITYQUEUE_H
#define PRIORITYQUEUES_SIMPLEPRIORITYQUEUE_H

template <class Value>
class SimplePriorityQueue: public PriorityQueue {

public:
    virtual void Insert(Value v);
    virtual Value DeleteMin();
};


#endif //PRIORITYQUEUES_SIMPLEPRIORITYQUEUE_H
