#include <iostream>
#include <cmath>
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

void fillRandomData(vector<long> &data,  int init, int offset)
{
    long increase_offset = 0;
    for(long i = 0, j = init; i < data.size(); i++,j++)
    {
        increase_offset += rand() % offset + 1;
        data[i] = increase_offset;
    }
}

/**
 * binary search with custom alpha to skew the tree
 */
int binary_search(vector<long> &data, long search, float alpha){
    int res = -1, min = 0, max = data.size();

    while (max >= min)
    {
        // alpha = 0.5
        int pointer =  min + (max-min) *alpha;
        /*
        cout << "min: " << min << endl;
        cout << "max: " << max << endl;
        cout << "pointer: " << pointer << endl;
        cout << "current: " << (*data)[pointer] << endl;
        */
        if(data[pointer] ==  search)
            return search;

        else if(data[pointer] < search) // move pointer to the right
        {
            // if new value is higher than previous result, it's a better choice
            if(data[pointer] > res)
                res = data[pointer];

            min = pointer + 1;
        }
        else if(data[pointer] > search) // move pointer to the left
        {
            max = pointer - 1;
        }

    }
    return res;
}

void outputCPUCounters(vector<int> &events, long_long *resultValues, long avg) {

    for(int i=0; i < events.size(); i++) {
        double value = double(resultValues[i]) / avg;
        cout << " " << value;
    }

    cout << endl;

}

int main(int argc, char **args) {
    const long avg = pow(10, 5); //10000
    init_papi();

    vector<int> events;
    events.push_back(PAPI_BR_MSP);
    events.push_back(PAPI_L1_DCM);
    events.push_back(PAPI_L2_DCM);
    long_long resultValues[events.size()];


    clock_t begin_t, end_t;
    double elapsed_secs;

    int s, result;
    // random seed
    srand(time(0));


    if(argc > 1) {
        switch (*args[1]) {
            case '1': {
                const long min_size = 10;
                const long max_size = pow(10, 7);
                float alp = 0.5;

                if (argc > 2) {
                    alp = atof(args[2]);
                }

                for (long x = min_size; x <= max_size; x *= 1.1) {

                    vector<long> data(x, 0);
                    fillRandomData(data, 1, 1);

                    int EventSet = begin_papi(events);
                    begin_t = clock();

                    for (long j = 0; j < avg; j++) {
                        s = rand() % data[data.size() - 1] + 1;
                        result = binary_search(data, s, alp);
                    }

                    end_t = clock();
                    end_papi(EventSet, resultValues);

                    double elapsed_secs = (double(end_t - begin_t) / CLOCKS_PER_SEC) / avg;
                    cout << x << " " << elapsed_secs;

                    outputCPUCounters(events, resultValues, avg);

                    //To avoid to much optimization
                    result = 42;

                    data.clear();
                }

                break;
            }
            case '2': {
                const long size = pow(10, 4);
                float increments = 0.03;
                for (float alp = increments; alp < 1; alp += increments) {
                    vector<long> data(size, 0);
                    fillRandomData(data, 1, 1);
                    int EventSet = begin_papi(events);

                    begin_t = clock();

                    // test avg times to make an average
                    for (int j = 0; j < avg; j++) {
                        s = rand() % data[data.size() - 1] + 1;
                        result = binary_search(data, s, alp);
                    }

                    end_t = clock();
                    end_papi(EventSet, resultValues);

                    double elapsed_secs = (double(end_t - begin_t) / CLOCKS_PER_SEC / avg);
                    cout << alp << " " << elapsed_secs;

                    outputCPUCounters(events, resultValues, avg);

                    //To avoid to much optimization
                    result = 42;

                    data.clear();
                }
                break;
            }
            default:
                cout << "No test chosen!" << endl;
                return -1;
        }
    }

    return 0;

}