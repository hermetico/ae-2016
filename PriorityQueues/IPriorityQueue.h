#ifndef PRIORITYQUEUE_IPRIORITYQUEUES_H
#define PRIORITYQUEUE_IPRIORITYQUEUES_H

#include <vector>

using namespace std;

template <class Value>
class IPriorityQueue {

public:
    virtual void Insert(Value v) = 0;
    virtual Value DeleteMin() = 0;

};


#endif //PRIORITYQUEUE_PRIORITYQUEUES_H
