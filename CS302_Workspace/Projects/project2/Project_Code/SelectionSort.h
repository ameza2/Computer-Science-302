// Abraham Meza //
// CS 302 - Project 2 //

//--------------------------------------------------------------------
//
//  SelectionSort.h
// 
//  Class declaration for Selection Sort Algorithm
//
//--------------------------------------------------------------------

#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

// header files //

#include <iostream>

// custom header files //

#include "DataInterface.h"

// namespace declarations //

using namespace std;

class SelectionSort : public DataInterface<int> { // class declaration (inherit virtual functions of DataInterface class)
public:
    SelectionSort(const int maxSize); // parameterized constructor

    int readFile(const string &filename); // method to read file of integer contents: should record all values
    bool writeFile(const string &filename) const; // method to write/export data to a file: should export all organized data
    
    int * sort(int &comps, int &swaps); // sorting algorithm method (selection sort)

    /////////////////////////////////////
    //       Testing Purposes Only     //
    /////////////////////////////////////

    void showarr() const; // display method (displays sorted data on terminal)
    void showarray() const; // dis play method (displays unsorted data on terminal)

private:
    int *array; // array pointer (int) (unsorted)
    int *arr; // array pointer (int) (sorted)
    int size; // size (int)
    int maxSize; // maxSize (int)

    int findLargestIndex(const int maxIndex, int &comps) const; // finds the largest integer value (via element) in given array data 
};

#endif // SELECTIONSORT_H