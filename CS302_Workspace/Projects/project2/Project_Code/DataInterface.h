// Abraham Meza //
// CS 302 - Project 2 //

//--------------------------------------------------------------------
//
//  DataInterface.h
// 
//  Class declaration for the Data Manipulation within Files (read/writes)
//
//--------------------------------------------------------------------

#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H

// header files //

#include <iostream>

// namespace declarations //

using namespace std;

template <class ItemType>  // template (class declaration)

class DataInterface{ // class declaration
public:
    virtual int readFile(const string &filename) = 0; // function to read file of integer contents: should record all values (made virtual to expand accessibility)
    
    virtual bool writeFile(const string &filename) const = 0; // function to write/export data to a file: should export all organized data (made virtual to expand accessibility)
};

#endif // DATAINTERFACE_H