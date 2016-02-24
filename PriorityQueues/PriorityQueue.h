
#ifndef PRIORITYQUEUE_PRIORITYQUEUES_H
#define PRIORITYQUEUE_PRIORITYQUEUES_H

#include <vector>

using namespace std;

template <class Value> class PriorityQueue {

private:
    vector<Value> _heap;

public:
    void Insert(Value v);
    Value DeleteMin();

};


#endif //PRIORITYQUEUE_PRIORITYQUEUES_H
