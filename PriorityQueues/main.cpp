#define DEBUGLEVEL 0
#include "Simple/SimplePriorityQueue.h"
#include <limits.h>
#include <iostream>
#include "Shared/Measure.h"
#include "Shared/Utils.h" // our utils
#include <stdlib.h>
#include <math.h>
#include "Sanders/shared/util.h" // the heaps util stuff
#include "Sanders/heap-CLR.h" // the slow heap
#include "Sanders/heap4.h" // the 4-ary heap
#include "Sanders/knheap.C"
//#include "heap4.h"
//#include "knheap.C"


#define rand32() (ran32State = 1664525 * ran32State + 1013904223)
#define getRandom() ((rand32()), (int)(ran32State >> 2))

using namespace std;


void performance_test(IPriorityQueue<int> *heap, int n)
{
    Measure measureUnit = Measure();

    int j;
    int newElem, k, v;
    //double insertSum=0, deleteSum=0;
    static int ran32State = 42 << 20;

    measureUnit.Begin();
    // PAPER TESTS
    // insert + delete + add -> from 0 until n, there will be n elements after the loop
    for (j = 0;  j < n;  j++) {
        heap->Insert(j);
        heap->DeleteMin();
        heap->Insert(j+1);
    }
    // delete + insert + delete -> from 0 to n, there will be 0 elements after the loop
    for (j = 0;  j < n;  j++) {
        heap->DeleteMin();
        heap->Insert(j);
        heap->DeleteMin();
    }



    measureUnit.End();

    // it gives us the time for each pair of operations
    measureUnit.Print<int>(n, n);

}


int main(int argc, char **argv)
{
    // first parameter the number of the elements in the queue
    // second parameter the number of iterations
    // third parameter the type of the heap
    int ran32State = 42 << 20;

    int heap_type =  atoi(argv[1]);
    IPriorityQueue<int> *common_heap;

    // por debajo de 1000 es lento
    for (long x = Utils::min_size; x <= Utils::max_size; x *= 1.1) {
        switch (heap_type) {
            case 0: {

                SimplePriorityQueue<int> test = SimplePriorityQueue<int>();
                common_heap = &test;
                performance_test(common_heap, x);
                break;
            }
            case 1: {
                Heap2<int, int> sanders_simple_heap = Heap2<int, int>(INT_MAX, -INT_MAX, x);
                common_heap = &sanders_simple_heap;
                performance_test(common_heap, x);
                break;
            }

            case 2: {
                Heap4<int, int> sanders_heap4 = Heap4<int, int>(INT_MAX, -INT_MAX, x);
                common_heap = &sanders_heap4;
                performance_test(common_heap, x);
                break;
            }
            case 3: {
               KNHeap<int, int> sanders_knheap = KNHeap<int, int>(INT_MAX, -INT_MAX); // doesn't need the capacity
               common_heap = &sanders_knheap;
               performance_test(common_heap, x);
               break;
           }

        }

    }


}

