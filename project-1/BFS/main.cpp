#include <iostream>

using namespace std;


void BuildBFSTreeRecursive(int *bfs, int min, int max, int index, int *sortedArray, double alpha) {

    int size = max-min+1;
    int pointerIndex = min + size*alpha;

    bfs[index] = sortedArray[pointerIndex];

    if(size > 1) {
        BuildBFSTreeRecursive(bfs, min, pointerIndex - 1, 2 * index + 1, sortedArray, alpha);
        BuildBFSTreeRecursive(bfs, pointerIndex + 1, max, 2 * index + 2, sortedArray, alpha);
    }

}

void BuildBFSTree(int *bfs, int *sortedArray, int size, double alpha) {
    BuildBFSTreeRecursive(bfs, 0, size-1, 0, sortedArray, alpha);
}

void GenerateInOrderArray(int *outputArray, int size) {
    for(int i=0; i < size; i++) {
        outputArray[i] = i+1;
    }
}

int BFSSearchRecursive(int query, int *tree, int size, int index) {
    if(index >= size) {
        return -1;
    }

    if(query < tree[index]) {
        return BFSSearchRecursive(query, tree, size, 2*index+1);
    } else if(query > tree[index]) {
        return BFSSearchRecursive(query, tree, size, 2*index+2);
    }

    return query;

}

int BFSSearch(int query, int *tree, int size) {
    return BFSSearchRecursive(query, tree, size, 0);
}

long BFSSearchIterative(int query, int *tree, int size) {

    long i = 0;

    while(i < size) {

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

int main() {

    const long min_size = 1000;
    const long max_size = 500000;
    const long avg = 100000;
    const double alpha = 0.5;
    int result;
    clock_t begin_t, end_t;

    srand(time(0));

    for (int x = min_size; x <= max_size; x += 1000) {
        int inOrder[x];
        int maxBfsTreeSize = 2*x;
        int bfsTree[maxBfsTreeSize];
        for(int i=0; i < maxBfsTreeSize; i++) {
            bfsTree[i] = 0;
        }
        int s;

        GenerateInOrderArray(inOrder, x);
        BuildBFSTree(bfsTree, inOrder, x, alpha);

        begin_t = clock();

        for (int j = 0; j < avg; j++) {
            s = 0 + (rand() % ((x * 4) - 0 + 1));
            result = BFSSearchIterative(s, bfsTree, maxBfsTreeSize);
        }

        end_t = clock();

        double elapsed_secs = (double(end_t - begin_t) / CLOCKS_PER_SEC) / avg;
        cout << x << " " << elapsed_secs << endl;

    }

    //To avoid the BFSSearch to be striped away at -O3 optimization
    cout << "Dummy: " << result << endl;

    return 0;
}