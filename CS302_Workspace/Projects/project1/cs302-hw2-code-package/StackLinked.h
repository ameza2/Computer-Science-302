// Abraham Meza //
// CS 302 - Project 2 //

//--------------------------------------------------------------------
//
//  StackLinked.h
// 
//  Class declaration for the linked list implementation of the Stack ADT
//
//--------------------------------------------------------------------

#ifndef STACKLINKED_H
#define STACKLINKED_H

#include <stdexcept>
#include <iostream>

using namespace std;

#include "Stack.h"

template <typename DataType>
class StackLinked;

template <typename DataType>
class StackLinked : public Stack<DataType>{

  public:
    StackLinked(int maxNumber = Stack<DataType>::MAX_STACK_SIZE);
    StackLinked(const StackLinked &other);
    StackLinked<DataType> &operator=(const StackLinked<DataType> &other);
    ~StackLinked();

    void push(const DataType &newDataItem) throw (logic_error);
    DataType pop() throw (logic_error);

    void clear();

    bool isEmpty() const;
    bool isFull() const;

    void showStructure() const;

  private:
    class StackNode{
      public:
    	StackNode(const DataType &nodeData, StackNode *nextPtr){
            dataItem = nodeData;
            next = nextPtr;
        }

    	DataType dataItem;
    	StackNode *next;
    };

    StackNode *top;
};

#endif		//#ifndef STACKLINKED_H

// Class Implementations (Templated) //

template <typename DataType>
StackLinked<DataType>::StackLinked(int maxNumber) : top(NULL){} // Constructor Definition
    // creates an empty stack (makes stack NULL)

template <typename DataType>
StackLinked<DataType>::StackLinked(const StackLinked &other){ // Copy Constructor Definition
    if (other.top == NULL){ // condition to check if other.stack is empty (NULL)
        top = NULL; // if so, assign top of stack to NULL
    }
    else{ // if other.top is not NULL
        // Declaration and Initialization //

        StackNode *current = other.top; // pointer declaration and initialization
        top = new StackNode(current -> dataItem, NULL); 
        StackNode *temp = top; // pointer declaration and initialization

        while (current != NULL){ // while loop to scan through other.stack information
            current = current -> next;
            temp -> next = new StackNode(current -> dataItem, NULL);
            temp = temp -> next;
        }

        temp -> next = NULL; // reset
        current = NULL; // reset
    }
}

template <typename DataType>
StackLinked<DataType> &StackLinked<DataType>::operator=(const StackLinked<DataType> &other){ // Overload Assignment Operator Definiton
    if(this != other){ // condition to check if both stacks contain the same data
        clear(); // if not, clear current stack first before assigning new data

        top = other -> top; // assigning new data into current stack
    }

    return *this; // return ALL data
}

template <typename DataType>
StackLinked<DataType>::~StackLinked(){ // Destructor Definition
    clear(); // calls clear() in order to clear and deallocate memory efficiently
}

template <typename DataType>
void StackLinked<DataType>::push(const DataType &newDataItem) throw (logic_error){ // push() method definition
    top = new StackNode(newDataItem, top); // pushes newDataItem to top of the stack
}

template <typename DataType>
DataType StackLinked<DataType>::pop() throw (logic_error){ // pop() method definition
    if (isEmpty()){ // condition to check if stack is empty (boolean)
        cout << "Invalid method; cannot pop() from an empty stack!!" << endl; // cout confirmation to let user know that pop() is unavailable in an empty() stack
    }
    else{ // if stack is not empty
        // Declaration and Initialization //

        StackNode *tempNode = top; // object pointer declaration and initalizaiton
        DataType tempData; // object declaration

        top = top -> next; // initalization; pointing to next object of data
        tempData = tempNode -> dataItem; // initaization; retrieving data

        delete tempNode; // deleting temporary pointer 
        tempNode = NULL; // assuring that temporary pointer is NULL (just in case)

        return tempData; // returning data 
    }
}

template <typename DataType>
void StackLinked<DataType>::clear(){ // clear() method definition
    while (isFull()){ // while loop that continues until stack is emtpy
        StackNode *current = top; // object pointer declaration and initialization
        top = top -> next; // assigning new data (next data)

        delete current; // deleting previous data
        current = NULL; // assuring that previous data is NULL (just in case)
    }
}

template <typename DataType>
bool StackLinked<DataType>::isEmpty() const{ // isEmpty() method definition
    return top == NULL; // returns boolean if top of stack is NULL
}

template <typename DataType>
bool StackLinked<DataType>::isFull() const{ // isFull() method definition
    return top != NULL; // returns boolean if top of stack is not NULL
}

//////////////////////////////////////
//// Testing Class Implementation //// 
////                              ////
//// Implementation should only   ////
//// be used for testing purposes ////
//// only!!                       ////
//////////////////////////////////////

template <typename DataType>
void StackLinked<DataType>::showStructure() const{ // showStructure() method definition
    if(isEmpty()){ // condition to check if stack is empty (NULL)
        cout << "The stack is empty!!" << endl; // cout confirmation to advise user that stack is empty
    }
    else{ // if stack is not empty
        cout << "The stack below is displayed from Top to Bottom." << endl; // cout confirmation to advise user the order of the stack

        StackNode *current = top; // object pointer declaration and initialization

        while(current != NULL){ // while loop that scans through the currentt stack until it reaches NULL
            cout << current -> dataItem << " "; // printing out data in stack
            current = current -> next; // object pointer moves onto new data 
        }
    }
    cout << endl; // formatting
}