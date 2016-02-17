//
// Created by laursen86 on 2/17/16.
//

#ifndef INORDER_PAPI_H
#define INORDER_PAPI_H
#include <papi.h>
#include <iostream>
#include <vector>

using namespace std;

class Measure {

private:

    vector<int> _events;
    long_long *_resultValues;
    int _eventSet;
    clock_t _begin_t, _end_t;

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

    void printCounters(long avg) {

        for(int i=0; i < _events.size(); i++) {
            double value = double(_resultValues[i]) / avg;
            cout << " " << value;
        }

        cout << endl;

    }

public:
    Measure() {
        init_papi();

        _events.push_back(PAPI_BR_MSP);
        _events.push_back(PAPI_L1_DCM);
        _events.push_back(PAPI_L2_DCM);

        _resultValues = new long_long[_events.size()];

    }

    ~Measure() {
        delete[] _resultValues;
    }

    void Begin() {
        _eventSet = PAPI_NULL;
        int rv;
        /* Create the Event Set */
        if ((rv = PAPI_create_eventset(&_eventSet)) != PAPI_OK)
            handle_error(rv);

        for(int i = 0; i < _events.size(); i++) {
            if ((rv = PAPI_add_event(_eventSet, _events[i])) != PAPI_OK)
                handle_error(rv);
        }

        /* Start counting events in the Event Set */
        if ((rv = PAPI_start(_eventSet)) != PAPI_OK)
            handle_error(rv);

        _begin_t = clock();
    }

    void End() {
        int rv;

        /* get the values */
        if ((rv = PAPI_stop(_eventSet, _resultValues)) != PAPI_OK)
            handle_error(rv);

        /* Remove all events in the eventset */
        if ((rv = PAPI_cleanup_eventset(_eventSet)) != PAPI_OK)
            handle_error(rv);

        /* Free all memory and data structures, EventSet must be empty. */
        if ((rv = PAPI_destroy_eventset(&_eventSet)) != PAPI_OK)
            handle_error(rv);

        _end_t = clock();
    }

    void Print(float x, const long avg = 1) {

        double elapsed_secs = (double(_end_t - _begin_t) / CLOCKS_PER_SEC) / avg;
        cout << x << " " << elapsed_secs;

        printCounters(avg);
    }


    void Print(long x, const long avg = 1) {

        double elapsed_secs = (double(_end_t - _begin_t) / CLOCKS_PER_SEC) / avg;
        cout << x << " " << elapsed_secs;

        printCounters(avg);
    }
};


#endif //INORDER_PAPI_H
