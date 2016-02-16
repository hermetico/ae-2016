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

void BuildBFSTreeRecursive(vector<long> &bfs, long min, long max, long index, vector<long> &sortedArray) {

    long size = max-min+1;
    long pointerIndex = min + size*0.5;

    bfs[index] = sortedArray[pointerIndex];

    if(size > 1) {
        BuildBFSTreeRecursive(bfs, min, pointerIndex - 1, 2 * index + 1, sortedArray);
        BuildBFSTreeRecursive(bfs, pointerIndex + 1, max, 2 * index + 2, sortedArray);
    }

}

void BuildBFSTree(vector<long> &bfs, vector<long> &sortedArray) {
    BuildBFSTreeRecursive(bfs, 0, sortedArray.size()-1, 0, sortedArray);
}


void fillRandomData(vector<long> &data,  int init, int offset)
{
    long increase_offset = 0;
    for(long i = 0, j = init; i < data.size(); i++,j++)
    {
        increase_offset += rand() % offset + 1;
        data[i] = increase_offset;
    }
}



void GenerateInOrderArray(vector<long> &outputArray) {
    for(long i=0; i < outputArray.size(); i++) {
        outputArray[i] = i+1;
    }
}

long BFSSearchRecursive(long query, const vector<long> &tree, long index) {
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

long BFSSearch(long query, const vector<long> &tree) {
    return BFSSearchRecursive(query, tree, 0);
}

long BFSSearchIterative(long query, const vector<long> &tree) {

    long i = 0;

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

void outputCPUCounters(vector<int> &events, long_long *resultValues, long avg) {

    for(int i=0; i < events.size(); i++) {
        double value = double(resultValues[i]) / avg;
        cout << " " << value;
    }

    cout << endl;

}

void incrementalTreeSize(long avg, int randMultiplier, vector<int> &events) {
    clock_t begin_t, end_t;
    long result;
    long_long resultValues[events.size()];
    const long min_size = 10;
    const long max_size = 10000000;

    for (long x = min_size; x <= max_size; x *= 1.1) {
        vector<long> inOrder(x);
        vector<long> bfsTree(2 * inOrder.size(), 0);
        long s;

        fillRandomData(inOrder, 1, randMultiplier);
        BuildBFSTree(bfsTree, inOrder);

        int EventSet = begin_papi(events);
        begin_t = clock();

        for (long j = 0; j < avg; j++) {
            s = rand() % (x * randMultiplier) + 1;

            result = BFSSearch(s, bfsTree);
        }

        end_t = clock();
        end_papi(EventSet, resultValues);

        double elapsed_secs = (double(end_t - begin_t) / CLOCKS_PER_SEC) / avg;

        cout << x << " " << elapsed_secs;

        outputCPUCounters(events, resultValues, avg);

    }

    result = 42;

}

void sameTreeSize(int runsAtLevel, int randMultiplier, vector<int> &events) {

    clock_t begin_t, end_t;
    long result;
    long_long resultValues[events.size()];
    const long size = 100000;

    vector<long> inOrder(size);
    vector<long> bfsTree(2 * inOrder.size(), 0);
    long s;

    fillRandomData(inOrder, 1, randMultiplier);
    BuildBFSTree(bfsTree, inOrder);

    long lastElement = inOrder[inOrder.size()-1];


    for(int i = 1; i <= 3; i++) {

        long startAt;

        switch (i)  {
            case 1:
                startAt = -lastElement;
                break;
            case 2:
                startAt = 0;
                break;
            case 3:
                startAt = lastElement;
                break;
        }

        for (int j = 0; j < runsAtLevel; j++) {
            int EventSet = begin_papi(events);
            begin_t = clock();

            s = startAt + rand() % lastElement + 1;

            for(int j=0; j< 100000; j++) {
                result = BFSSearch(s, bfsTree);
            }

            end_t = clock();
            end_papi(EventSet, resultValues);

            double elapsed_secs = (double(end_t - begin_t) / CLOCKS_PER_SEC) / 100000;

            cout << s << " " << elapsed_secs;

            outputCPUCounters(events, resultValues, 100000);
        }



    }

    result = 42;

}


int main(int argc, char **args) {

    const long avg = 100000;

    vector<int> events;
    events.push_back(PAPI_BR_MSP);
    events.push_back(PAPI_L1_DCM);
    events.push_back(PAPI_L2_DCM);
    long resultValues[events.size()];

    long result;
    int runsAtLevel = 10;
    int randMultiplier;
    srand(time(0));
    init_papi();

    if(argc > 1) {
        switch (*args[1]) {
            case '1':
                randMultiplier = 1;
                incrementalTreeSize(avg, randMultiplier, events);
                break;
            case '2':
                randMultiplier = 4;
                incrementalTreeSize(avg, randMultiplier, events);
                break;
            case '3':

                randMultiplier = 4;
                sameTreeSize(runsAtLevel, randMultiplier, events);
                break;

            default:
                cout << "No test chosen!" << endl;
                return -1;
        }
    }





    return 0;
}
