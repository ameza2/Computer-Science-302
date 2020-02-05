// Abraham Meza //
// CS 302 - Project 3 //

//--------------------------------------------------------------------
//
//  BinaryTreeInterface.h
// 
//  Class declaration and initalization for Binary Tree Interface
//
//--------------------------------------------------------------------

#ifndef BINARY_TREE_INTERFACE
#define BINARY_TREE_INTERFACE

// header files //

#include <iostream>
#include <memory>

// custom header files //

#include "BinaryNode.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"

// namespace declarations //

using namespace std;

template<class ItemType>
class BinarySearchTreeInterface : BinaryNode<ItemType>{ // class declaration w/ inheritance to BinaryNode class (inherit virtual functions of Binary Node class)
    private:
        shared_ptr<BinaryNode<ItemType>> rootPtr; // pointer of object (root pointer) declaration

    public:
        //------------------------------------------------------------ 
        // Public Virtual Methods Section. (all initialized to 0)
        //------------------------------------------------------------

        virtual bool isEmpty() const = 0;
        virtual int getHeight() const = 0;
        virtual int getNumberOfNodes() const = 0;

        virtual ItemType getRootData() const = 0;
        virtual void setRootData(const ItemType &newData) = 0;

        virtual bool add(const ItemType &newEntry) = 0;
        virtual bool remove(const ItemType &target) = 0;
        virtual void clear() = 0;

        virtual ItemType getEntry(const ItemType &anEntry) const = 0;
        virtual bool contains(const ItemType &anEntry) const = 0;

        //------------------------------------------------------------ 
        // Public Virtual Traversals Section. (all initialized to 0)
        //------------------------------------------------------------

        virtual void preorderTraverse(void visit(ItemType&)) const = 0;
        virtual void inorderTraverse(void visit(ItemType&)) const = 0;
        virtual void postorderTraverse(void visit(ItemType&)) const = 0;
}; // end of class declaration

#endif // BINARY_TREE_INTERFACE_H