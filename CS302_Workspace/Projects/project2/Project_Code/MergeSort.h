// Abraham Meza //
// CS 302 - Project 2 //

//--------------------------------------------------------------------
//
//  MergeSort.h
// 
//  Class declaration for Merge Sort Algorithm
//
//--------------------------------------------------------------------

#ifndef MERGESORT_H
#define MERGESORT_H

// header files //

#include <iostream>

// custom header files //

#include "DataInterface.h"

using namespace std;

class MergeSort : public DataInterface<int> { // class declaration (inherit virtual functions of DataInterface class)
public:
    MergeSort(const int maxSize); // parameterized constructor

    int readFile(const string &filename); // method to read file of integer contents: should record all values
    bool writeFile(const string &filename) const; // method to write/export data to a file: should export all organized data

    void merge_sort(int *arr, int beginning, int final, int &comps, int &swaps); // sorting algorithm method (merge sort)
    
    void showarr() const; // display method (displays sorted data on terminal)
    void showarray() const; // display method (displays unsorted data on terminal)

    int *getArray() const; // *getArr() method; allows access to array data (arr)
    int getSize() const; // getSize() method; allows access to the current size of the array

private:
    int *array; // array pointer (int)
    int *arr; // array pointer (int)
    int size; // size (int)
    int maxSize; // maxSize (int)

    void merge(int *arr, int beginning, int midpoint, int final, int &comps, int &swaps); // merge algorithm method: finalizes sorting algoritm (merge sorted array (recursive))
};

#endif // MERGESORT_H