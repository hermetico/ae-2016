//
// Created by hermetico on 2/13/16.
//

#include "DFSArray.h"
#include <iostream>
#include <math.h>
#include <limits>


/**
 * Main constructor, the other ones end up calling this one
 */
DFSArray::DFSArray(float alpha)
{
    this->alpha = alpha;
    this->verbose = false;
}


DFSArray::DFSArray(): DFSArray(0.5){};



DFSArray::DFSArray(vector<int> *input_data): DFSArray(0.5)
{
    this->fill(input_data);
}

DFSArray::DFSArray(vector<int> *input_data, float alpha): DFSArray(alpha)
{
    this->fill(input_data);
}

void DFSArray::setAlpha(float alpha)
{
    this->alpha = alpha;
}


void DFSArray::fill(vector<int> *input_data)
{
    this->depth = 0;
    this->bottom_reached = false;
    this->tree.clear();
    this->visited.clear();

    this->fillArrayRecursive(input_data, 0, input_data->size(), 0, 0);

}

void DFSArray::fillArrayRecursive(vector<int> *input_data, int init, int end, int v, unsigned index)
{
    int size = end - init;
    if(size == 0)
    {
        if(bottom_reached) return;

        this->depth = v - 1;
        this->bottom_reached = true;

        return;
    }

    int pointer = init + (int)( size * this->alpha );

    // we need to fill some nodes of the tree with null values in order to
    // keep the structure
    while(tree.size() <= index) tree.push_back(0);

    if(verbose) {
        cout << "\ninit: " << init;
        cout << "\ntreeSize: " << tree.size();
        cout << "\nend: " << end;
        cout << "\nv: " << v;
        cout << "\nindex: " << index;
        cout << "\nsize: " << size;
        cout << "\npointer: " << pointer;
        cout << "\ndepth: " << this->depth;
        cout << "\rbottom_reached: " << this->bottom_reached;
        cout << endl;
    }

    tree[index] = (*input_data)[pointer];

    // left branch
    this->fillArrayRecursive(input_data, init, pointer, v + 1, index + 1);
    // right branch
    this->fillArrayRecursive(input_data, pointer + 1, end, v + 1, (int) index + pow(2, depth - v));
}

int DFSArray::length()
{
    return tree.size();
}


int DFSArray::predecessor(int key)
{
    this->visited.clear();
    this->possible_response = - numeric_limits<int>::max();
    this->predecessorRecursive(key, 0, 0);
    return this->possible_response;
}


void DFSArray::predecessorRecursive(int key, unsigned int index,  int v)
{

    // we need to know if an index has ben visited in order to know if
    // we are in a leaf
    while(index >= this->visited.size()) this->visited.push_back(false);


    if(verbose) {
        cout << "\nindex: " << index;
        cout << "\nvisited: " << visited[index];
        cout << "\nvisited length: " << this->visited.size();
        cout << "\ndepth: " << this->depth;
        cout << "\nvalue: " << tree[index];
        cout << "\nv: " << v;
        cout << endl;
        cout << "visited nodes" << endl;
        printVisited();
    }

    if(key == tree[index])
    {
        if(verbose) cout << "Exiting, found the exact number" << endl;

        this->possible_response = tree[index];
        return;
    }

    if(visited[index] || v > this->depth)
    {
        if(verbose) cout << "Exiting, node visited, or v > depth" << endl;
        return;
    }

    visited[index] = true;

    if(tree[index] < key) // right branch
    {
        if(verbose) cout << "\nbranching right" << endl;

        if(tree[index] > this->possible_response) this->possible_response = tree[index];

        this->predecessorRecursive(key,  (int) index + pow(2, this->depth - v), v + 1);
    }
    else // left branch
    {
        if(verbose) cout << "\nbranching left" << endl;

        this->predecessorRecursive(key, index + 1, v + 1);
    }
}



void DFSArray::printArray()
{
    cout <<  "[";
    for(unsigned int i = 0; i < tree.size(); i++)
    {
        cout <<  tree[i] << ",";
    }
    cout <<  "]" << endl;
}

void DFSArray::printVisited()
{
    cout <<  "[";
    for(unsigned int i = 0; i < visited.size(); i++)
    {
        cout <<  visited[i] << ",";
    }
    cout <<  "]" << endl;
}

void DFSArray::setVerboseMode(bool mode)
{
    this->verbose = mode;
}

DFSArray::~DFSArray()
{

}