// Abraham Meza //
// CS 302 - Project 2 //

//--------------------------------------------------------------------
//
//  SelectionSort.cpp
// 
//  Class implementation for Selection Sort Algorithm
//
//--------------------------------------------------------------------

// header files //

#include <iostream>
#include <cstring>
#include <fstream>

// custom header filess //

#include "SelectionSort.h"

// namespace declarations //

using namespace std;

const int RESET = 0; // const for resetting int variables to default (0)

SelectionSort::SelectionSort(const int maxSize) : size(0), maxSize(maxSize) { // parameterized constructor definition (w/ initalizer list [default size, and max size of list])
    array = new int[maxSize]; // creating a 1D array to store data in (efficient memory allocation through maxSize limitation)
}

int SelectionSort::readFile(const string &filename) { // readFile() method definition
    ifstream inputStream; // declares file manipulation

    inputStream.open(filename); // opens file indicated by user (input file)

    int i = 0; // variable declaration and initalization
    size = RESET; // reassign size to default (0); avoid size errors for each file

    while (inputStream && i < maxSize){ // while loop that scans through file for data until it reaches maxSize or EOF
        inputStream >> array[i]; // data entry transfered to array list

        i++; // i incrementation (travels through indexes)
        size++; // size incrementation (keeps track of the size of the list)
    }

    inputStream.close(); // close opened (input) file

    return i; // return number of elements in the array
}

bool SelectionSort::writeFile(const string &filename) const { // writeFile() method definition
    ofstream outputStream; // declares file manipulation
    
    outputStream.open(filename); // opens file indicated by program (output file)

    for (int i = 0; i < size; i++){ // for loop that scans through array data
        outputStream << arr[i] << endl; // prints sorted data to screen
    }

    outputStream.close(); // close opened (output) file

    return true; // returns bool (data has been sorted)
}

int * SelectionSort::sort(int &comps, int &swaps) { // sort() method definition

    arr = new int[size]; // creating a 1D array to copy data in (efficient memory allocation through size limitation)

    for (int i = 0; i < size; i++){ // for loop that naviagtes through array data
        arr[i] = array[i]; // copying array data (new/old)
    }

    for (int final = size - 1; final > 0; final--){ // for loop that starts from the final element of the list and sorts its way forward
        int largest = findLargestIndex(final + 1, comps); // finds largest value of the list

        swap(arr[largest], arr[final]); // swaps largest element with the bottom-most element
        swaps++; // swaps incrementation (keeps tracks of number of swaps during sorting algorithm)
    }

    return arr; // return array data (sorted data)
}

int SelectionSort::findLargestIndex(const int maxIndex, int &comps) const { // findLargestIndex() method definition
    int travelingIndex = 0; // variable declaration and initalization

    for (int currentIndex = 1; currentIndex < maxIndex; currentIndex++){ // for loop that scans through array data from first to last 
        comps++; // comparison incrementation (keeps track of number of comparisons within array)

        if (arr[travelingIndex] < arr[currentIndex]){ // if statement (keeps track of which index integer value is greater)
            travelingIndex = currentIndex; // if scanned element integer is greater, then assign greater index to traveling index
        }
    }

    return travelingIndex; // return greatest integer value (via index/element)
}



    /////////////////////////////////////
    //       Testing Purposes Only     //
    /////////////////////////////////////


void SelectionSort::showarr() const { // showarr() method definition
    for (int i = 0; i < maxSize; i++){ // for loop that scans through array data
        cout << "[" << i << "] " << arr[i] << endl; // prints sorted data to screen
    }

    cout << endl; // formatting 
}

void SelectionSort::showarray() const{ // showarray() method definition 
    for (int i = 0; i < maxSize; i++){ // for loop that scans through array data
        cout << "[" << i << "] " << array[i] << endl; // prints sorted data to screen
    }

    cout << endl; // formatting 
}