// Abraham Meza //
// CS 302 - Project 2 //

//--------------------------------------------------------------------
//
//  MergeSort.cpp
// 
//  Class implementation for Merge Sort Algorithm
//
//--------------------------------------------------------------------

// header files //

#include <iostream>
#include <cstring>
#include <fstream>

// custom header files //

#include "MergeSort.h"

// namespace declarations //

using namespace std;

const int RESET = 0; // const for resetting int variables to default (0)

MergeSort::MergeSort(const int maxSize) : size(0), maxSize(maxSize) { // parameterized contructor definition
    array = new int[maxSize]; // creating a 1D array to store data in (efficient memory allocation through maxSize limitation)
    arr = new int[maxSize];
}

int MergeSort::readFile(const string &filename) { // readFile() method definition
    ifstream inputStream;  // declares file manipulation

    inputStream.open(filename); // opens file indicated by user (input file)

    int i = 0; // variable declaration and initalization
    size = RESET;

    while (inputStream && i < maxSize) { // while loop that scans through file for data until it reaches maxSize or EOF
        inputStream >> array[i]; // data entry transfered to array list

        i++; // i incrementation (travels through indexes)
        size++; // size incrementation (keeps track of the size of the list)
    }

    arr = new int[size]; // creating a 1D array to copy data in (efficient memory allocation through size limitation)

    for (int i = 0; i < size; i++){ // for loop that naviagtes through array data
        arr[i] = array[i]; // copying array data (new/old)
    }

    return i; // return number of elements in the array
}

bool MergeSort::writeFile(const string &filename) const { // writeFile() method definition
    ofstream outputStream; // declares file manipulation
    
    outputStream.open(filename); // opens file indicated by program (output file)

    for (int i = 0; i < size; i++) { // for loop that scans through array data, and exports index data to output file
        outputStream << arr[i] << endl; // array data transfered to output file in accordance to index
    }

    outputStream.close(); // close opened (output) file

    return true; // returns bool (data has been sorted)
}

void MergeSort::merge_sort(int *arr, int beginning, int final, int &comps, int &swaps) { // merge_sort() method definition
    if (beginning < final) { // if array is not sorted (merge sort)
        int midpoint = beginning + (final - beginning) / 2; // variable declaration and initialization: finds midpoint of array list (splits array into two parts (Divide and Conquer))

        // Divide and Conquer //

        merge_sort(arr, beginning, midpoint, comps, swaps); // merge_sort() algorithm on first half of the array: sorts all elements before midpoint (and midpoint) recursively
        merge_sort(arr, midpoint + 1, final, comps, swaps); // merge_sort() algorithm on second half of the array: sorts all elements after midpoint recursively

        merge(arr, beginning, midpoint, final, comps, swaps);
    }
}

void MergeSort::merge(int *arr, int beginning, int midpoint, int final, int &comps, int &swaps) { // merge() method definition
    int i, j, k; // variable declaration

    int array1 = midpoint - beginning + 1; // first half of the array list (data)
    int array2 = final - midpoint; // second half of the array list (data)

    int First[array1], Second[array2]; // array declaration and initialization: two seperate array lists

    for (i = 0; i < array1; i++) { // for loop that scans through all array1 data
        First[i] = arr[beginning + i]; // array data transfer
    }

    for (j = 0; j < array2; j++) { // for loop that scans through all array2 data
        Second[j] = arr[midpoint + 1 + j]; // array data transfer
    }

    i = RESET; // variable re-assigned to 0 (reset)
    j = RESET; // variable re-assinged to 0 (reset)
    k = beginning; // variable assigned to beginning of array list

    while (i < array1 && j < array2) { // while loop that scans through both array data
        comps++; // comps incrementation (keeps track of number of comparisons)

        if (First[i] <= Second[j]) { // if statement that checks condition of both arrays: (if data of indicated index on first array is less than/equal to data of indicated index on second array)
            arr[k] = First[i]; // if first array data is less or equal to second array data, then it becomes next in line of the sorted list

            i++; // i incrementation (array data navigation via indexes)
        } else {
            arr[k] = Second[j]; // if second array data is greater than first array data, then it becomes next in line of the sorted list

            j++; // j incrementation (array data navigation via indexes)
        }

        k++; // k incrementation (moves onto next index of sorted array list)
    }

    while (i < array1) { // while loop that transfers all of first array data to sorted list
        arr[k] = First[i]; // data transfer

        i++; // i incrementation (array data navigation via indexes)
        k++; // k incrementation (moves onto next index of sorted array list)
    }

    while (j < array2) { // while loop that transfers all of second array data to sorted list
        arr[k] = Second[j]; // data transfer

        j++; // j incrementation (array data navigation via indexes)
        k++; // k incrementation (moves onto next index of sorted array list)
    }
}

int * MergeSort::getArray() const { // *getArr() method definition
    return arr; // return array data (array)
}

int MergeSort::getSize() const { // getSize() method definition 
    return size; // return current size of array (arr)
}

    /////////////////////////////////////
    //       Testing Purposes Only     //
    /////////////////////////////////////

void MergeSort::showarr() const { // showarr() method definition
    for (int i = 0; i < getSize(); i++) { // for loop that scans through array data
        cout << "[" << i << "] " << arr[i] << endl; // prints sorted data to screen
    }

    cout << endl; // formatting 
}

void MergeSort::showarray() const{ // showarray() method definition 
    for (int i = 0; i < getSize(); i++){ // for loop that scans through array data
        cout << "[" << i << "] " << array[i] << endl; // prints sorted data to screen
    }

    cout << endl; // formatting 
}