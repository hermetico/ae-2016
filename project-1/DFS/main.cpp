#include <iostream>
#include <vector>
#include "DFSArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <papi.h>
using namespace std;

void handle_error(int error) {
    cout << error << endl;
}

void init_papi() {
    int retval = PAPI_library_init(PAPI_VER_CURRENT);
    if (retval != PAPI_VER_CURRENT && retval < 0) {
        printf("PAPI library version mismatch!\n");
        exit(1);
    }
    if (retval < 0) handle_error(retval);

}

int begin_papi(vector<int> &Events) {
    int EventSet = PAPI_NULL;
    int rv;
    /* Create the Event Set */
    if ((rv = PAPI_create_eventset(&EventSet)) != PAPI_OK)
        handle_error(rv);

    for(int i = 0; i < Events.size(); i++) {
        if ((rv = PAPI_add_event(EventSet, Events[i])) != PAPI_OK)
            handle_error(rv);
    }

    /* Start counting events in the Event Set */
    if ((rv = PAPI_start(EventSet)) != PAPI_OK)
        handle_error(rv);
    return EventSet;
}

void end_papi(int EventSet, long_long *returnValue) {
    int rv;

    /* get the values */
    if ((rv = PAPI_stop(EventSet, returnValue)) != PAPI_OK)
        handle_error(rv);

    /* Remove all events in the eventset */
    if ((rv = PAPI_cleanup_eventset(EventSet)) != PAPI_OK)
        handle_error(rv);

    /* Free all memory and data structures, EventSet must be empty. */
    if ((rv = PAPI_destroy_eventset(&EventSet)) != PAPI_OK)
        handle_error(rv);

}



void fillRandomData(vector<int> *data, int length, int init, int offset)
{
    int min_offset = 0, increase_offset;
    for(int i = 0, j = init; i < length; i++,j++)
    {
        increase_offset = min_offset + (rand() % (offset - 0 + 1));
        j += increase_offset;
        data->push_back(j);
    }
}

void fillRandomData(vector<int> *data,  int init, int offset)
{
    int min_offset = 0, increase_offset;
    for(int i = 0, j = init; i < data->size(); i++,j++)
    {
        increase_offset = min_offset + (rand() % (offset - 0 + 1));
        j += increase_offset;
        (*data)[i] = j;
    }
}

void testDFS()
{
    int k = 18, init = 1, offset = 10, key = 67;
    float alpha = .8;
    DFSArray *tree;
    vector<int> *data = new vector<int>;

    fillRandomData(data, k , init, offset);

    cout << "data size: " << data->size() << endl;
    cout << "data content: ";
    cout <<  "[";
    for( unsigned int i = 0; i < data->size(); i++)
    {
        cout << (*data)[i] << ",";
    }
    cout <<  "]" << endl;


    tree = new DFSArray(alpha);
    tree->fill(data);
    cout << "tree size: " << tree->length() << endl;
    cout << "tree content: " << endl;


    tree->printArray();

    delete(tree);
    delete(data);
    return;
}



int main(int argc, char **args) {

    // test params
    const long_long min_size = 10;
    const long_long max_size = 10000000;
    const long_long avg = 100000;
    //const long_long avg = 10;

    // tree and data params
    const int init = 1;
    const float alpha = .5;
    int offset = argc > 1 ? int(*args[1] -'0') : 0;

    
    DFSArray *tree;

    // papi params
    vector<int> events;
    events.push_back(PAPI_BR_MSP);
    events.push_back(PAPI_L1_DCM);
    events.push_back(PAPI_L2_DCM);
    long_long resultValues[events.size()];


    long_long result;
    clock_t begin_t, end_t;

    init_papi();
    srand(time(0));
    tree = new DFSArray(alpha);

    for (long_long x = min_size; x <= max_size; x *= 1.1) {
        long_long s;
        vector<int> *data = new vector<int>(x);
        fillRandomData(data, init, offset);

        tree->fill(data);
        int EventSet = begin_papi(events);
        begin_t = clock();

        for (long_long j = 0; j < avg; j++) {
            // TODO try take a value between 0 and the last value of an array
            s = rand() % (x * (offset + 1) ) + 1;
            result = tree->predecessor(s);
        }

        end_t = clock();
        end_papi(EventSet, resultValues);

        double elapsed_secs = (double(end_t - begin_t) / CLOCKS_PER_SEC) / avg;

        cout << x << " " << elapsed_secs;

        for(int i=0; i < events.size(); i++) {
            double value = double(resultValues[i]) / avg;
            cout << " " << value;
        }


        cout << endl;

    }


    result = 42;

    return 0;
}
