#include <iostream>
#include <vector>
#include "DFSArray.h"
using namespace std;

#include "../Shared/Measure.h"
#include "../Shared/Utils.h"



void testDFS(int offset, float alpha)
{
    int k = 23, init = 1, query;

    alpha = 0.5;
    DFSArray *tree;
    vector<long> *data = new vector<long>(k);
    cout << "creating an array of size " << k << " and multiplier " << offset << endl;
    Utils::FillRandomData((*data), init, offset);

    cout << "data size: " << data->size() << endl;
    cout << "data content: ";

    Utils::printVector(data);


    tree = new DFSArray(alpha);
    tree->fill(data);
    cout << "tree size: " << tree->length() << endl;
    cout << "tree content: " << endl;


    tree->printArray();
    query = rand() % ( data->back() + 1 );
    cout << "query: " << query << " result: " << tree->predecessor(query) << endl;

    delete(tree);
    delete(data);
    return;
}

void  basic_performance_test(int offset, float alpha)
{


    Measure measureUnit = Measure();

    srand(time(0));
    const int init = 1; // init number for the random data
    long query;
    long highest_number; // to be considered for the query
    long result;

    DFSArray *tree;
    tree = new DFSArray(alpha);

    for (long x = Utils::min_size; x <= Utils::max_size; x *= 1.1) {

        vector<long> *data = new vector<long>(x);
        Utils::FillRandomData((*data), init, offset);
        tree->fill(data);
        highest_number = data->back();

        // starts the counters
        measureUnit.Begin();


        for (long j = 0; j < Utils::avg; j++) {
            query = rand() % ( highest_number + 1 );
            result = tree->predecessor(query);
        }

        // stops the counters and prints the results
        measureUnit.End();
        measureUnit.Print<long>(x, Utils::avg);

        result = 42;
        delete(data);
    }



}


void test_alpha(float alpha_step) {

    Measure measureUnit = Measure();

    srand(time(0));
    DFSArray *tree;
    long  result, highest_number, query;

    for (float alpha = 0.01; alpha < 0.99 ; alpha += alpha_step) {

        tree = new DFSArray(alpha);
        vector<long> *data = new vector<long>(Utils::max_size);

        Utils::FillRandomData((*data), 1, 2);
        tree->fill(data);
        highest_number = data->back();

        measureUnit.Begin();

        for (long j = 0; j < Utils::avg; j++) {
            query = rand() % (highest_number + 1);
            result = tree->predecessor(query);
        }

        // stops the counters and prints the results
        measureUnit.End();
        measureUnit.Print<float>(alpha, Utils::avg);

        result = 42;

        delete(tree);
        delete(data);
    }


    result = 42;
}

int main(int argc, char **args) {

    int test = argc > 1 ? int(*args[1] -'0') : 0;
    int offset = argc > 2 ? int(*args[2] -'0') : 1;
    int alpha_test = argc > 3 ? int(*args[3] -'0') : 0;
    float alpha_step = 0.01;

    srand(time(0));

    switch (test)
    {
        case 0:
            testDFS(offset, 0.5);
            break;
        case 1:
            switch(alpha_test){
                case 0:
                    basic_performance_test(offset, 0.75);
                    break;
                case 1:
                    basic_performance_test(offset, 0.8);
                    break;
                case 2:
                    basic_performance_test(offset, 0.85);
                    break;
            }
            break;
        case 2:
            test_alpha(alpha_step);
            break;

    }

    return 0;
}
