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

void performance_test(IPriorityQueue<int> *heap, int n)
{
    static int ran32State = 42 << 20;
    int j, newElem;

    // PAPER TESTS
    // insert + delete + add -> from 0 until n, there will be n elements after the loop
    for (j = 0;  j < n;  j++)
    {
        newElem = getRandom(); // non consecutive values!!
        heap->Insert(newElem);
        heap->DeleteMin();
        heap->Insert(newElem);
    }

    // delete + insert + delete -> from 0 to n, there will be 0 elements after the loop
    for (j = 0;  j < n;  j++)
    {

        heap->DeleteMin();
        heap->Insert(newElem);
        heap->DeleteMin();
    }



}

int main(int argc, char **argv)
{
    int heap_type =  atoi(argv[1]);


    Measure measureUnit = Measure();


    for (long x = Utils::min_size; x <= Utils::max_size; x *= 1.5) {

        switch (heap_type) {
            case 0: {

                IPriorityQueue<int> *queue;
                VectorHeap<int> vectorHeap = VectorHeap<int>();
                queue = &vectorHeap;

                // warmup
                performance_test(queue, x);
                measureUnit.Begin();
                for (long j = 0; j <= Utils::avg; j++) {
                    performance_test(queue, x);
                }
                measureUnit.End();
                measureUnit.Print<int>(x, x * Utils::avg);

                break;
            }
            case 1: {
                IPriorityQueue<int> *queue;
                Heap2<int, int> sanders_simple_heap = Heap2<int, int>(INT_MAX, -INT_MAX, x);
                queue = &sanders_simple_heap;

                // warmup
                performance_test(queue, x);
                measureUnit.Begin();
                for (long j = 0; j <= Utils::avg; j++) {
                    performance_test(queue, x);
                }
                measureUnit.End();
                measureUnit.Print<int>(x, x * Utils::avg);

                break;
            }

            case 2: {
                IPriorityQueue<int> *queue;
                Heap4<int, int> sanders_heap4 = Heap4<int, int>(INT_MAX, -INT_MAX, x);
                queue = &sanders_heap4;

                // warmup
                performance_test(queue, x);
                measureUnit.Begin();
                for (long j = 0; j <= Utils::avg; j++) {
                    performance_test(queue, x);
                }
                measureUnit.End();
                measureUnit.Print<int>(x, x *Utils::avg);

                break;
            }
            default: {
                IPriorityQueue<int> *queue;
                KNHeap<int, int> sanders_knheap = KNHeap<int, int>(INT_MAX, -INT_MAX); // doesn't need the capacity
                queue = &sanders_knheap;

                // warmup
                performance_test(queue, x);
                measureUnit.Begin();
                for (long j = 0; j <= Utils::avg; j++) {
                    performance_test(queue, x);
                }
                measureUnit.End();
                measureUnit.Print<int>(x, x * Utils::avg);

                break;
           }
        }





    }


}

