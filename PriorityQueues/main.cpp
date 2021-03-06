#define DEBUGLEVEL 0
#include <limits.h>
#include <iostream>
#include "Shared/Measure.h"
#include "Shared/Utils.h" // our utils
#include <stdlib.h>
#include <math.h>
#include "Sanders/shared/util.h" // the heaps util stuff
#include "Sanders/heap-CLR.h" // the slow heap
#include "Sanders/heap4.h" // the 4-ary heap
#include "Sanders/knheap.C" // the fast one
#include "IPriorityQueue.h"
#include "Simple/VectorHeap.h"

using namespace std;

#define rand32() (ran32State = 1664525 * ran32State + 1013904223)
#define getRandom() ((rand32()), (int)(ran32State >> 2))

static int ran32State = 42 << 20;

void randomTest(IPriorityQueue<int> *heap, int n) {
    int j;

    // PAPER TESTS
    // insert + delete + add -> from 0 until n, there will be n elements after the loop
    for (j = 0;  j < n;  j++)
    {
        heap->Insert(getRandom());
        heap->DeleteMin();
        heap->Insert(getRandom());
    }

    // delete + insert + delete -> from 0 to n, there will be 0 elements after the loop
    for (j = 0;  j < n;  j++)
    {
        heap->DeleteMin();
        heap->Insert(getRandom());
        heap->DeleteMin();
    }

}

void sequentialTest(IPriorityQueue<int> *heap, int n) {
    int j;

    // PAPER TESTS
    // insert + delete + add -> from 0 until n, there will be n elements after the loop
    for (j = 0;  j < n;  j++)
    {
        heap->Insert(j);
        heap->DeleteMin();
        heap->Insert(j+1);
    }

    // delete + insert + delete -> from 0 to n, there will be 0 elements after the loop
    for (j = 0;  j < n;  j++)
    {
        heap->DeleteMin();
        heap->Insert(j);
        heap->DeleteMin();
    }

}


void performance_test(IPriorityQueue<int> *heap, int n, void (*testLoop)(IPriorityQueue<int>*, int))
{

    //Warm up
    testLoop(heap, n);

    Measure measureUnit = Measure();
    measureUnit.Begin();

    for(int i = 0; i <= Utils::avg; i++) {
        testLoop(heap, n);
    }

    measureUnit.End();

    // it gives us the time for each pair of operations (Think so)
    measureUnit.Print<int>(n, 3*n*Utils::avg);

}

int main(int argc, char **argv)
{
    int heap_type =  atoi(argv[1]);

    void (*testLoop)(IPriorityQueue<int> *heap, int n);

    if(argc > 2 && *argv[2] == 'r') {
        testLoop = &randomTest;
    } else {
        testLoop = &sequentialTest;
    }

    // por debajo de 1000 es lento
    for (long x = Utils::min_size; x <= Utils::max_size; x *= 1.1) {
        switch (heap_type) {
            case 0: {
                VectorHeap<int, int> vectorHeap = VectorHeap<int, int>(x);
                performance_test(&vectorHeap, x, testLoop);
                break;
            }
            case 1: {
                Heap2<int, int> sanders_simple_heap = Heap2<int, int>(INT_MAX, -INT_MAX, x);
                performance_test(&sanders_simple_heap, x, testLoop);
                break;
            }

            case 2: {
                Heap4<int, int> sanders_heap4 = Heap4<int, int>(INT_MAX, -INT_MAX, x);
                performance_test(&sanders_heap4, x, testLoop);
                break;
            }
            case 3: {
               KNHeap<int, int> sanders_knheap = KNHeap<int, int>(INT_MAX, -INT_MAX); // doesn't need the capacity
               performance_test(&sanders_knheap, x, testLoop);
               break;
           }

        }

    }


}

