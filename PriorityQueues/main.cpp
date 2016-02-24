#include <iostream>
#include "Simple/SimplePriorityQueue.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    SimplePriorityQueue<int> test = SimplePriorityQueue<int>();
    IPriorityQueue<int> *kotest = &test;
    kotest->Insert(10);
    int k = kotest->DeleteMin();

    return 0;
}