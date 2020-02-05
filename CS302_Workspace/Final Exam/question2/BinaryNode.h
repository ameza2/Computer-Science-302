// Abraham Meza //
// CS 302 - Project 3 //

//--------------------------------------------------------------------
//
//  BinaryNode.h
// 
//  Class declaration and implementation for Binary Nodes
//
//--------------------------------------------------------------------

#ifndef BINARY_NODE
#define BINARY_NODE

// header files //

#include <iostream>
#include <memory>

// namespace declarations //

using namespace std;

template<class ItemType>
class BinaryNode{ // class declaration 
    private:
        ItemType item; // object declaration
        shared_ptr<BinaryNode<ItemType>> leftChildPtr; // pointer of object (Left Child Pointer) declaration
        shared_ptr<BinaryNode<ItemType>> rightChildPtr; // pointer of object (Right Child Pointer) declaration
        
    public:
        BinaryNode(); // default constructor
        BinaryNode(const ItemType &otherItem); // paramterized constructor
        BinaryNode(const ItemType &otherItem, shared_ptr<BinaryNode<ItemType>> leftPtr, shared_ptr<BinaryNode<ItemType>> rightPtr); // parameterized constructor

        void setItem(const ItemType &otherItem); // method setItem(): assigns passed value/variable to item data 
        ItemType getItem() const; // method getItem(): get current value of Item data
        
        shared_ptr<BinaryNode<ItemType>> getLeftChildPtr() const; // method getLeftChildPtr(): gets value of left child pointer
        shared_ptr<BinaryNode<ItemType>> getRightChildPtr() const; // method getRightChildPtr(): gets value of right child pointer
        
        void setLeftChildPtr(shared_ptr<BinaryNode<ItemType>> leftPtr); // method setLeftChildPtr(): sets the value of left child pointer to the value of left pointer within BST
        void setRightChildPtr(shared_ptr<BinaryNode<ItemType>> rightPtr); // method setRightChildPtr(): sets the value of right child pointer to the value of right pointer within BST

        bool isLeaf() const; // boolean expression: checks to see if both left and right child pointers are NULL
}; // end of class declaration

template<class ItemType>
BinaryNode<ItemType>::BinaryNode() : item(0), leftChildPtr(nullptr), rightChildPtr(nullptr){} // default construtor definition w/ initalizer list: initalizes all tracking and modification variables to 0/NULL

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& otherItem) : item(otherItem), leftChildPtr(nullptr), rightChildPtr(nullptr){} // parameterized constructor definition w/ initalizer list: assigns values passed (otherItem) to tracking and modificiation variables

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& otherItem, shared_ptr<BinaryNode<ItemType>> leftPtr, shared_ptr<BinaryNode<ItemType>> rightPtr) : item(otherItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr){} // parameterized constructor definition w/ initalizer list: assigns values passed (otherItem) to tracking, modificiation, and object oriented variables

template<class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType& otherItem){ // setItem() method definition
    item = otherItem; // assigns passed variable (otherItem) to indicated variable (item)
}

template<class ItemType>
ItemType BinaryNode<ItemType>::getItem() const{ // getItem() method definition
    return item; // returns value of item 
}

template<class ItemType>
bool BinaryNode<ItemType>::isLeaf() const{ // isLeaf() boolean expression (function)
    return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr)); // returns boolean (checks both child pointers for value of NULL)
}

template<class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(shared_ptr<BinaryNode<ItemType>> leftPtr){ // setLeftChildPtr() method definition
    leftChildPtr = leftPtr; // assigns passed variable (leftPtr) to indicated variable (leftChildPtr)
}

template<class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(shared_ptr<BinaryNode<ItemType>> rightPtr){ // setRightChildPtr() method definition
    rightChildPtr = rightPtr; // assigns passed variable (rightPtr) to indicated variable (rightChildPtr)
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNode<ItemType>::getLeftChildPtr() const{ // getLeftChildPtr() method definition
    return leftChildPtr; // returns value of leftChildPtr 
}  

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNode<ItemType>::getRightChildPtr() const{ // getRightChildPtr() method definition
    return rightChildPtr; // returns value of rightChildPtr 
}

#endif // BINARY_NODE_H