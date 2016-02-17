#include <iostream>
#include <vector>
#include "../Shared/Measure.h"
#include "../Shared/Utils.h"
#include "BFS.h"

using namespace std;

int main(int argc, char **args) {
    long result;
    int randMultiplier;
    srand(time(0));

    Measure measureUnit = Measure();

    if(argc > 1) {
        switch (*args[1]) {
            case '1':
                randMultiplier = 1;
                break;
            case '2':
                randMultiplier = 4;
                break;
            default:
                cout << "No test chosen!" << endl;
                return -1;
        }

        for (long x = Utils::min_size; x <= Utils::max_size; x *= 1.1) {
            vector<long> inOrder(x);
            Utils::FillRandomData(inOrder, 1, randMultiplier);
            BFS bfsTree = BFS(inOrder);

            measureUnit.Begin();

            for (long j = 0; j < Utils::avg; j++) {
                long s = rand() % inOrder[inOrder.size()-1] + 1;
                result = bfsTree.Predecessor(s);
            }

            measureUnit.End();
            measureUnit.Print(x, Utils::avg);

            result = 42;

            inOrder.clear();
        }

    } else {
        cout << "No test chosen!" << endl;
        return -1;
    }

    return 0;
}
