// Abraham Meza //
// CS 302 - Project 2 //

//--------------------------------------------------------------------
//
//  StackArray.h
// 
//  Class declaration for the linked implementation of the Stack ADT
//
//--------------------------------------------------------------------

#ifndef STACKARRAY_H
#define STACKARRAY_H

#include <stdexcept>
#include <iostream>

using namespace std;

const int EMPTY = -1; // const variable to signify an empty stack (array implementation)

#include "Stack.h"

template <typename DataType>
class StackArray : public Stack<DataType> {
  public:
    StackArray(int maxNumber = Stack<DataType>::MAX_STACK_SIZE);
    StackArray(const StackArray& other);
    StackArray& operator=(const StackArray& other);
    ~StackArray();

    void push(const DataType& newDataItem) throw (logic_error);
    DataType pop() throw (logic_error);

    void clear();

    bool isEmpty() const;
    bool isFull() const;

    void showStructure() const;

  private:
    int maxSize;
    int top;
    DataType* dataItems;
};

#endif		//#ifndef STACKARRAY_H

// Class Implementations (Templated) //

template<typename DataType>
StackArray<DataType>::StackArray(int maxNumber) : maxSize(maxNumber), top(EMPTY){ // Constructor Definition
    dataItems = new DataType[maxSize]; // creates a stack in accordance to the maxSize (makes stack NULL)
};

template<typename DataType>
StackArray<DataType>::StackArray(const StackArray &other) : maxSize(other.maxSize), top(other.top){ // Copy Constructor Definition
    dataItems = new DataType[maxSize]; // creates a stack in accordance to the maxSize (copies data from other.stack)

    for (int i = 0; i < top; i++){ // for loop that is used to scan through stack
        dataItems[i] = other.dataItems[i]; // assigns value from other.stack to original stack elements
    }
}

template<typename DataType>
StackArray<DataType>& StackArray<DataType>::operator=(const StackArray &other){ // Overload Assignment Operator Definiton
    if (this != other){ // condition to check if both stacks contain the same data
        delete dataItems; // properly delete and deallocate array memory/value(s)

        maxSize = other.maxSize; // assiging maxSize of other.stack to original stack 
        top = other.top; // assigning top of other.stack to original stack (top)
        
        dataItems = new DataType[maxSize]; // creates a stack in accordance to the maxSize (copies data from other.stack)

        for (int i = 0; i < top; i++){ // for loop that is used to scan through stack
            dataItems[i] = other.dataItems[i]; // assigns value from other.stack to original stack elements
        }
    }
    return this; // returns new (copied) stack
}

template<typename DataType>
StackArray<DataType>::~StackArray(){ // Destructor Definition
    clear(); // calls clear() in order to clear and deallocate memory efficiently
}

template<typename DataType>
void StackArray<DataType>::push(const DataType &newDataItem) throw(logic_error){ // push() method definition
    dataItems[++top] = newDataItem; // pushes newDataItem to top of the stack (creates space)
}

template<typename DataType>
DataType StackArray<DataType>::pop() throw(logic_error){ // pop() method definition
    if (isEmpty()){ // condition to check if stack is empty (boolean)
        cout << "Invalid method; cannot pop() from an empty stack!!" << endl;
    }
    else{ // if stack is not empty
      top--; // removes space (deletes to element data)
      return dataItems[top + 1]; // returning data
    }
}

template<typename DataType>
void StackArray<DataType>::clear(){ // clear() method definition
    top = EMPTY; // assigns top of stack to invalid (NULL); causes stack to collapse and delete efficiently
}

template<typename DataType>
bool StackArray<DataType>::isEmpty() const{ // isEmpty() method definition
    return top == EMPTY; // returns boolean if top of stack is invalid (NULL)
}

template<typename DataType>
bool StackArray<DataType>::isFull() const {
    return top == maxSize - 1; // returns boolean if stack has occupied all avaiable space (maxSize - 1)
}

//////////////////////////////////////
//// Testing Class Implementation //// 
////                              ////
//// Implementation should only   ////
//// be used for testing purposes ////
//// only!!                       ////
//////////////////////////////////////

template<typename DataType>
void StackArray<DataType>::showStructure() const{ // showStructure() method definition
    if (isEmpty()) { // condition to check if stack is empty (NULL)
      cout << "The stack is empty!!" << endl; // cout confirmation to advise user that stack is empty
    } 
    else{ // if stack is not empty
      cout << "The stack below is displayed from Bottom to Top." << endl; // cout confirmation to advise user the order of the stack

      for (int i = 0; i <= top; i++) { // for loop that scans through the current stack until all data has been scanneed
          cout << dataItems[i] << " "; // printing out data in stack
      }
    }

    cout << endl; // formatting
}