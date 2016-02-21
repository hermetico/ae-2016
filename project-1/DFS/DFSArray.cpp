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

    this->fillArrayRecursive(input_data, 0, input_data->size(), 0, 0);

}

void DFSArray::fillArrayRecursive(vector<int> *input_data, int init, int end, int v, unsigned index)
{
    int size = end - init;
    if(size == 0)
    {
        if(bottom_reached)
            return;

        this->depth = v - 1;
        this->bottom_reached = true;
        return;
    }

    int pointer = init + (int)( size * this->alpha );


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

    tree.push_back( (*input_data)[pointer] );

    // left branch
    this->fillArrayRecursive(input_data, init, pointer, v + 1, index + 1);
    // right branch
    this->fillArrayRecursive(input_data, pointer + 1, end, v + 1, (int) index + (this->alpha * (size + 1)));
}

int DFSArray::length()
{
    return tree.size();
}


int DFSArray::predecessor(int key)
{
    this->possible_response = - numeric_limits<int>::max();
    this->predecessorRecursive(key, 0, this->tree.size());
    return this->possible_response;
}


void DFSArray::predecessorRecursive(int key, unsigned int index,  int size)
{




    if(verbose) {
        cout << "\nindex: " << index;
        cout << "\ndepth: " << this->depth;
        cout << "\nvalue: " << tree[index];
        cout << endl;
    }

    if(key == tree[index])
    {
        if(verbose) cout << "Exiting, found the exact number" << endl;

        this->possible_response = tree[index];
        return;
    }

    if (size == 0 )
    {
        if(verbose) cout << "Exiting, exact number not found" << endl;

        return;
    }


    if(key < tree[index]) // left branch
    {
        if(verbose) cout << "\nbranching left" << endl;

        this->predecessorRecursive(key, index + 1, floor(this->alpha * size));
    }
    else
    {
        if(verbose) cout << "\nbranching right" << endl;

        this->possible_response = tree[index];
        this->predecessorRecursive(key, index + 1 + floor(this->alpha * size),
                                   ceil( (1 - this->alpha) * size) - 1);

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


void DFSArray::setVerboseMode(bool mode)
{
    this->verbose = mode;
}

DFSArray::~DFSArray()
{

}