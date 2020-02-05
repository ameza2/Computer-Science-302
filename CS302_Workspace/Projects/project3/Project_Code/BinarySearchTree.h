// Abraham Meza //
// CS 302 - Project 3 //

//--------------------------------------------------------------------
//
//  BinarySearchTree.h
// 
//  Class declaration and implementation for Binary Search Tree
//
//--------------------------------------------------------------------

/** Link-based implementation of the ADT binary search tree. @file BinarySearchTree.h */

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

// header files //

#include <iostream>
#include <memory>


// custom header files //

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"

// namespace declarations //

using namespace std;

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>{ // class declaration w/ inheritance to BNT class (inherit virtual functions of BNT class)
    private:
        shared_ptr<BinaryNode<ItemType>> rootPtr; // pointer of object (root pointer) declaration
        
    protected:
        //------------------------------------------------------------
        // Protected Utility Methods Section:
        // Recursive helper methods for the public methods. 
        //------------------------------------------------------------

        shared_ptr<BinaryNode<ItemType>> placeNode(shared_ptr<BinaryNode<ItemType>> subTreePtr, shared_ptr<BinaryNode<ItemType>> newNode); // object method(): search nodes in BST (search tree)

        shared_ptr<BinaryNode<ItemType>> findNode(shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType& target, bool& isSuccessful) const; // object method(): finding specified nodes in BST
        
        shared_ptr<BinaryNode<ItemType>> removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& success) override; // object method(): removing specified values from BST
        shared_ptr<BinaryNode<ItemType>> removeNode(shared_ptr<BinaryNode<ItemType>> nodePtr); // object method(): removing specified nodes from BST
        shared_ptr<BinaryNode<ItemType>> removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> subTreePtr, ItemType inorderSuccessor); // object method(): removing leftmost nodes from BST
        
    public:
        //------------------------------------------------------------ 
        // Constructor and Destructor Section. 
        //------------------------------------------------------------

        BinarySearchTree(); // default constructor 
        BinarySearchTree(const ItemType& rootItem); // parameterized constructor
        BinarySearchTree(const BinarySearchTree<ItemType>& tree); // parameterized constructor
        virtual ~BinarySearchTree(); // destructor 
        
        //------------------------------------------------------------ 
        // Public Methods Section. 
        //------------------------------------------------------------

        // All methods will contain 'override' in order to implement specified implementations for BST; AVOID DOUBLE IMPLEMENTATION/DECLARATION //

        bool isEmpty() const override; // boolean expression; method isEmpty(): checks to see if BST is empty (NULL)
        int getHeight() const override; // method getHeight(): provides the height of BST (int)
        int getNumberOfNodes() const override; // method getNumberOfNodes(): provides total number of Nodes within BST (int)

        ItemType getRootData() const throw(PrecondViolatedExcept) override; // object method() w/PrecondViolatedExcept: gets root pointer data 
        void setRootData(const ItemType& newData) const throw(PrecondViolatedExcept); // method setRootData(): assigns passed value/variable to root pointer data

        bool add(const ItemType& newEntry) override; // boolean expression; method add(): checks to see if addition of value to BST was a success
        bool remove(const ItemType& anEntry) override; // boolean expression; method remove(): checks to see if removal of value from BST was a success
        void clear() override; // method clear(): clears data from BST

        ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException) override; // object method() w/NotFoundException: gets entry data 
        bool contains(const ItemType& anEntry) const override; // boolean expression; method contains(): checks to see if BST 'contains' values (NOT EMPTY)
        
        //------------------------------------------------------------ 
        // Public Traversals Section. 
        //------------------------------------------------------------

        void preorderTraverse(void visit(ItemType&)) const override; // method preorder(): provides preorder transversal of BST
        void inorderTraverse(void visit(ItemType&)) const override; // method inorder(): provides inorder transversal of BST
        void postorderTraverse(void visit(ItemType&)) const override; // method postorder(): provides postorder transversal of BST

        //------------------------------------------------------------ 
        // Overloaded Operator Section. 
        //------------------------------------------------------------

        BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide); // object assignment operator
}; // end of class declaration

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::placeNode(shared_ptr<BinaryNode<ItemType>> subTreePtr, shared_ptr<BinaryNode<ItemType>> newNode){ // method placeNode() definition
    if (subTreePtr == nullptr){ // if statement (checks to see if SubTree data is NULL pointer)
        return newNode; // return newNode data
    }

    else{ // if SubTree data is not NULL
        if (subTreePtr->getItem() > newNode->getItem()){ // if statment condition (if SubTree data > NewNode data)
            subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr() , newNode)); // place newNode data into left of SubTree
        }
        else{ // (if NewNode data > SubTree data)
            subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr() , newNode)); // place newNode data into right of SubTree
        }
        
        return subTreePtr; // return new data modification of BST (new SubTree)
    }
}


template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& success){ // method removeValue() definition
    if (subTreePtr == nullptr){ // if statement (checks to see if SubTree value is NULL pointer)
        success = false; // boolean success assignned to 'false'
    }
    else if (subTreePtr->getItem() == target){ // else if statement (checks to see if SubTree data equal to passed value/variable data (target))
        subTreePtr = removeNode(subTreePtr); // remove targeted data

        success = true; // boolean success assigned 'true'
    }
    else if (subTreePtr->getItem() > target){ // else if statement (checks to see if SubTree data is greater than to passed value/variable data (target))
        shared_ptr<BinaryNode<ItemType>> tempPointer = removeValue(subTreePtr->getLeftChildPtr(), target, success); // object variable declaration and initialization (temp pointer) [ left ]
        subTreePtr->setLeftChildPtr(tempPointer); // SubTree pointer assigned left child pointer assigned (tempPointer)
    }
    else{
        shared_ptr<BinaryNode<ItemType>> tempPointer = removeValue(subTreePtr->getRightChildPtr(), target, success); // object variable declaration and initialization (temp pointer) [ right ]
        subTreePtr->setRightChildPtr(tempPointer); // SubTree pointer right child pointer assigned (tempPointer)
    }
    
    return subTreePtr; // return new data modification of BST (new SubTree)
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData){ // method add() definition 
    shared_ptr<BinaryNode<ItemType>> newNodePointer = make_shared<BinaryNode<ItemType>>(newData); // object variable declaration and initialization (newNode pointer)
    rootPtr = placeNode(rootPtr, newNodePointer); // add newNode into corresponding BST (root ptr)

    return true; // return boolean true (success)
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeNode(shared_ptr<BinaryNode<ItemType>> nodePtr){ // method removeNode() definition 
    if(nodePtr->getLeftChildPtr() == nullptr || nodePtr->getRightChildPtr() == nullptr){ // if statement (checks to see if either child pointer is NULL pointer)
        nodePtr = nullptr; // node pointer equals NULL pointer

        return nodePtr; // return data of node pointer
    }
    else if((nodePtr->getLeftChildPtr() !=nullptr) != (nodePtr->getRightChildPtr() !=nullptr)){ // else if statement (checks to see if boolean are the same, which checks to see if both child pointers are NOT NULL) [different booleans]
        shared_ptr<BinaryNode<ItemType>> ConnectionPtr = nullptr; // object variable declaration and initialization (connecetion pointer)

        if(nodePtr->getLeftChildPtr() !=nullptr){ // if statement (if left child pointer is not equal to NULL)
            ConnectionPtr = nodePtr->getLeftChildPtr(); // connection to left child pointer
        }
        else{ // (if left child pointer is equal to NULL)
            ConnectionPtr = nodePtr->getRightChildPtr(); // connection to left right pointer
        }

        return ConnectionPtr; // return connection pointer data
    }
    else{ // (if either child pointer is NOT NULL and match booleans)
        shared_ptr<BinaryNode<ItemType>> tempPointer = removeLeftmostNode(nodePtr->getRightChildPtr(), nodePtr->getItem()); // object variable declaration and initialization (temp pointer); remove leftmost node of leftmost SubTree

        nodePtr->setRightChildPtr(tempPointer); // node ponter is assigned right child pointer data (temp pointer)
        nodePtr->setItem(nodePtr->getItem()); // node pointer is assigned specified item data

        return nodePtr; // return node pointer data
    }
}


template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> subTreePtr, ItemType inorderSuccessor){ // method removeLeftmostNode() definition
    if(subTreePtr->getLeftChildPtr() == nullptr){ // if statement (if left child pointer is equal to NULL pointer)
        inorderSuccessor = subTreePtr->getItem(); // inorderSuccessor assigned specified item data

        return removeNode(subTreePtr); // return removeNode(): removes leftmost node
    }
    else{ // (if left child pointer is not equal to NULL)
        shared_ptr<BinaryNode<ItemType>> tempPointer = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor); // object variable declaration and initialization (temp pointer)
        subTreePtr->setLeftChildPtr(tempPointer); // SubTree pointer is assigned left child pointer data (temp pointer)

        return subTreePtr; // return new data modification of BST (new SubTree)
    }
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::findNode(shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType& target, bool& isSuccessful) const{ // method findNode() definition
    if(treePtr == nullptr){ // if statement (if tree pointer is equal to NULL pointer)
        return nullptr; // return NULL pointer data
    }
    else if(treePtr->getItem() == target){ // else if statemenet (if tree pointer (item) is equal to passed value/variable (target))
        isSuccessful = true; // boolean isSuccessful assigned 'true'
        return treePtr; // return tree pointer data
    }
    else if(treePtr->getItem() > target){ // else if statement (if tree pointer (item) is greater than passed value/variable (target))
        return findNode(treePtr->getLeftChildPtr(), target, isSuccessful); // return findNode() of left child pointer
    }
    else{ // (if trr pointer is neither NULL pointer or greater than or equal to target data)
        return findNode(treePtr->getRightChildPtr(), target, isSuccessful); // return findNode() of right child pointer
    }
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(){} // constructor definition

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType &rootItem) : rootPtr(make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr)){} // parameterized constructor definition

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType> &tree){ // copy constructor definition
    rootPtr = this->copyTree(tree.rootPtr); // root pointer data is assinged to the root data of copied tree (copying data)
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree(){ // destructor definition
    this->destroyTree(rootPtr); // call destroyTree(): deletes all tree data (proper memory deallocation for BST)
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const{ // method getHeight() definition
    return this->getHeightHelper(rootPtr); // return height of BST
}


template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const{ // method isEmpty() definition
    return rootPtr == nullptr; // checks to see if root pointer of tree equals NULL: if so, it is empty (true)
}


template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const{ // method getNumberOfNodes definition
    return this->getNumberOfNodesHelper(rootPtr); // returns numbere of nodes within BST
}

template<class ItemType>
void BinarySearchTree<ItemType>::clear(){ // method clear() definition
    this->destroyTree(rootPtr); // call destroyTree() in order to clear BST (proper memory deallocation)

    this->rootPtr.reset(); // reset root pointer
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const throw(PrecondViolatedExcept){ // method getRootData() definition
    if (isEmpty()){ // if statement(checks to see if BST is empty)
        throw PrecondViolatedExcept("Error! getRootData() method was called with an empty tree.");
    }
        
    return this->rootPtr->getItem(); // return root pointer data of BST
}

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType &newData) const throw(PrecondViolatedExcept){ // method setRootData() definition
    if (isEmpty()){ // if statement(checks to see if BST is empty)
        this->rootPtr = make_shared<BinaryNode<ItemType>>(newData, nullptr, nullptr); // assigns new root pointer
    }
    else{ // (if BST is NOT EMPTY)
       this->rootPtr->setItem(newData); // assigns old root pointer to passed value/variable data
    }
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType &anEntry) const throw(NotFoundException){ // method getEntry() definition
    bool isSuccessful = false; // boolean variable declaration and initalization (false): success?
    
    shared_ptr<BinaryNode<ItemType>> binaryNodePtr = findNode(rootPtr, anEntry, isSuccessful); // object variable declaration and initialization (binary node pointer; finds entry node)
    
    if (isSuccessful){ // if statement (if isSuccessful is true)
        return binaryNodePtr->getItem(); // return binary node data (binary node pointer is assigned entry data)
    }
    else{ // (if isSuccessful is false)
        throw NotFoundException("Entry cannot be located within tree!!"); // cout prompt (ERROR)
    }
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const{ // method contains() definition
    bool isSuccessful = false; // boolean variable declaration and initalization (false): success?

    findNode(rootPtr, anEntry, isSuccessful); // call findNode() to look for data

    return isSuccessful; // return boolean isSucessful
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &anEntry){ // method remove() definition
    bool isSuccessful = false; // boolean variable declaration and initalization (false): success?

    rootPtr = removeValue(rootPtr, anEntry, isSuccessful);  // call removeValue() to remove target data

    return isSuccessful; // return boolean isSucessful
}

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const{ // method preorderTraverse() definition
    this->preorder(visit, rootPtr); // preorder() algorithm/function
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const{ // method inorderTraverse() definition
    this->inorder(visit, rootPtr); // inorder() algorithm/function
}

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const{ // method postorderTraverse() definition
    this->postorder(visit, rootPtr); // postorder() algorithm/function
}

#endif // BINARY_SEARCH_TREE_H