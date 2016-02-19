#include <iostream>
#include <cmath>
#include <vector>
#include "InOrder.h"
#include "../Shared/Measure.h"
#include "../Shared/Utils.h"

using namespace std;

int main(int argc, char **args) {
    Measure measureUnit = Measure();

    int s, result;
    // random seed
    srand(time(0));


    if(argc > 1) {
        switch (*args[1]) {
            case '1': {
                float alp = 0.5;

                if (argc > 2) {
                    alp = atof(args[2]);
                }

                for (long x = Utils::min_size; x <= Utils::max_size; x *= 1.1) {

                    vector<long> data(x, 0);
                    Utils::FillRandomData(data, 1, 1);
                    InOrder inOrder = InOrder(data, alp);

                    measureUnit.Begin();

                    for (long j = 0; j < Utils::avg; j++) {
                        s = rand() % data[data.size() - 1] + 1;
                        result = inOrder.Predecessor(s);
                    }

                    measureUnit.End();
                    measureUnit.Print<long>(x, Utils::avg);

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
                    vector<long> data(Utils::max_size, 0);
                    Utils::FillRandomData(data, 1, 1);
                    InOrder inOrder = InOrder(data, alp);

                    measureUnit.Begin();

                    // test avg times to make an average
                    for (int j = 0; j < Utils::avg; j++) {
                        s = rand() % data[data.size() - 1] + 1;
                        result = inOrder.Predecessor(s);
                    }

                    measureUnit.End();
                    measureUnit.Print<float>(alp, Utils::avg);

                    //To avoid to much optimization
                    result = result+2;

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