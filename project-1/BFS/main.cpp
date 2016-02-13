#include <iostream>
#include <vector>
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

/*    std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
    << " MINOR: " << PAPI_VERSION_MINOR(retval)
    << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";*/
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

void BuildBFSTreeRecursive(vector<long_long> &bfs, long_long min, long_long max, long_long index, vector<long_long> &sortedArray) {

    long_long size = max-min+1;
    long_long pointerIndex = min + size*0.5;

    bfs[index] = sortedArray[pointerIndex];

    if(size > 1) {
        BuildBFSTreeRecursive(bfs, min, pointerIndex - 1, 2 * index + 1, sortedArray);
        BuildBFSTreeRecursive(bfs, pointerIndex + 1, max, 2 * index + 2, sortedArray);
    }

}

void BuildBFSTree(vector<long_long> &bfs, vector<long_long> &sortedArray) {
    BuildBFSTreeRecursive(bfs, 0, sortedArray.size()-1, 0, sortedArray);
}

void GenerateInOrderArray(vector<long_long> &outputArray) {
    for(long_long i=0; i < outputArray.size(); i++) {
        outputArray[i] = i+1;
    }
}

long_long BFSSearchRecursive(long_long query, const vector<long_long> &tree, long_long index) {
    if(index >= tree.size()) {
        return -1;
    }

    if(query < tree[index]) {
        return BFSSearchRecursive(query, tree, 2*index+1);
    } else if(query > tree[index]) {
        return BFSSearchRecursive(query, tree, 2*index+2);
    }

    return query;

}

long_long BFSSearch(long_long query, const vector<long_long> &tree) {
    return BFSSearchRecursive(query, tree, 0);
}

long_long BFSSearchIterative(long_long query, const vector<long_long> &tree) {

    long_long i = 0;

    while(i < tree.size()) {

        if(query == tree[i]) {
            return query;
        }

        if(query < tree[i]) {
            i = 2*i+1;
        } else {
            i = 2*i+2;
        }

    }

    return -1;

}

int main(int argc, char **args) {

    const long_long min_size = 10;
    const long_long max_size = 10000000;
    const long_long avg = 100000;

    vector<int> events;
    events.push_back(PAPI_BR_MSP);
    events.push_back(PAPI_L1_DCM);
    events.push_back(PAPI_L2_DCM);
    long_long resultValues[events.size()];

    long_long result;
    clock_t begin_t, end_t;

    init_papi();

    srand(time(0));

    for (long_long x = min_size; x <= max_size; x *= 1.1) {
        vector<long_long> inOrder(x);
        vector<long_long> bfsTree(2*inOrder.size(), 0);
        long_long s;

        GenerateInOrderArray(inOrder);
        BuildBFSTree(bfsTree, inOrder);

        int EventSet = begin_papi(events);
        begin_t = clock();

        for (long_long j = 0; j < avg; j++) {
            s = 0 + (rand() % ((x * 4) - 0 + 1));

            if(argc > 1 && *args[1] == 'i') {
                result = BFSSearchIterative(s, bfsTree);
            } else {
                result = BFSSearch(s, bfsTree);
            }
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

    //To avoid the BFSSearch to be striped away at -O3 optimization
    result = 42;	

    return 0;
}
