// Abraham Meza //
// CS 302 - Project 3 //

//--------------------------------------------------------------------
//
//  BinaryNodeTree.h
// 
//  Class declaration and implementation for Binary Node Tree
//
//--------------------------------------------------------------------

#ifndef BINARY_NODE_TREE
#define BINARY_NODE_TREE

// header files //

#include <iostream>
#include <memory>

// custom header files //

#include "BinaryNode.h"
#include "BinaryTreeInterface.h"
#include "PrecondViolatedExcept.h"
#include "NotFoundException.h"

// namespace declarations //

using namespace std;

template<class ItemType>
class BinaryNodeTree : public BinarySearchTreeInterface<ItemType>{ // class declaration w/ inheritance to BST Interface (inherit virtual functions of BST class)
    private:
        shared_ptr<BinaryNode<ItemType>> rootPtr; // pointer of object (root pointer) declaration
    
    protected:
        //------------------------------------------------------------
        // Protected Utility Methods Section:
        // Recursive helper methods for the public methods. 
        //------------------------------------------------------------

        int getHeightHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const; // method getHeightHelper(): provides height of tree
        int getNumberOfNodesHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const; // method getNumberofNodes(): provides number of nodes within BNT (contributes to height)
        
        shared_ptr<BinaryNode<ItemType>> balAdd(shared_ptr<BinaryNode<ItemType>> subTreePtr, shared_ptr<BinaryNode<ItemType>> newNodePtr); // object method(): adding values to BNT
        shared_ptr<BinaryNode<ItemType>> moveValUp(shared_ptr<BinaryNode<ItemType>> subTreePtr); // object method(): moves values within BNT (upwards)
        shared_ptr<BinaryNode<ItemType>> findNode(shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType &target, bool& success) const; // object method(): finds specified Node
        shared_ptr<BinaryNode<ItemType>> copyTree(const shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const; // object method(): finds original root pointer

        virtual shared_ptr<BinaryNode<ItemType>> removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& success); // virtual object method(): removes value within BNT 

        void destroyTree(shared_ptr<BinaryNode<ItemType>> subTreePtr); // method DestroyTree(): removes all data from BNT (proper memory deallocation)
        
        void preorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const; // method preorder(): provides preorder transversal of BNT
        void inorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const; // method inorder(): provides inorder transversal of BNT
        void postorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const; // method postorder(): provides postorderr transversal of BNT
        
    public:
        //------------------------------------------------------------ 
        // Constructor and Destructor Section. 
        //------------------------------------------------------------
    
        BinaryNodeTree(); // default constructor 
        BinaryNodeTree(const ItemType& rootItem); // parameterized constructor
        BinaryNodeTree(const ItemType& rootItem, const shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr, const shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr); // paramterized constructor
        BinaryNodeTree(const BinaryNodeTree<ItemType>& tree); // copy constructor (object oriented)
        virtual ~BinaryNodeTree(); // destructor 
        
        //------------------------------------------------------------ 
        // Public Methods Section. 
        //------------------------------------------------------------

        bool isEmpty() const; // boolean expression; method isEmpty(): checks to see if BNT is empty (NULL)
        bool contains(const ItemType &anEntry) const; // boolean expression; method contains(): checks to see if BNT 'contains' values (NOT EMPTY)

        int getHeight() const; // method getHeight(): provides the height of BNT (int)
        int getNumberOfNodes() const; // method getNumberOfNodes(): provides total number of Nodes within BNT (int)

        void getRootData(const ItemType &newData); // method getRootData(): provides root pointer data
        void setRootData(const ItemType &newData); // method setRootData(): assigns passed value/variable to root pointer data

        bool add(const ItemType &newData); // boolean expression; method add(): checks to see if addition of value to BNT was a success
        bool remove(const ItemType &data); // boolean expression; method remove(): checks to see if removal of value from BNT was a success

        void clear(); // method clear(): clears data from BNT
    
        //------------------------------------------------------------ 
        // Public Traversals Section. 
        //------------------------------------------------------------

        void preorderTraverse(void visit(ItemType&)) const; // method preorder(): provides preorder transversal of BNT
        void inorderTraverse(void visit(ItemType&)) const; // method inorder(): provides inorder transversal of BNT
        void postorderTraverse(void visit(ItemType&)) const; // method postorder(): provides postorder transversal of BNT

        ItemType getRootData() const throw(PrecondViolatedExcept); // object method() w/PrecondViolatedExcept: gets root pointer data 
        ItemType getEntry(const ItemType &anEntry) const throw(NotFoundException); // object method() w/NotFoundException: gets entry data 
        
        //------------------------------------------------------------ 
        // Overloaded Operator Section. 
        //------------------------------------------------------------

        BinaryNodeTree& operator=(const BinaryNodeTree &rightHandSide); // object assignment operator
}; // end of class declaration

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const{ // method getHeightHelper() definition
    if (subTreePtr == nullptr){ // if statement (checks to see if SubTree data is NULL)
        return 0; // end method
    }
    else{ // if SubTree data is not NULL
        return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr())); // return height of BNT
    }
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const{ // method getNumberOfNodesHelper() definition
    if (subTreePtr == nullptr){ // if statement (checks to see if SubTree data is NULL)
        return 0; // end method
    }
    else{
        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr()); // return number of nodes within BNT
    }
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::balAdd(shared_ptr<BinaryNode<ItemType>> subTreePtr, shared_ptr<BinaryNode<ItemType>> newNodePtr){ // method balAdd() definition
    if (subTreePtr == nullptr){ // if statement (checks to see if SubTree data is NULL)
        return newNodePtr; // add newNode data
    }
    else{ // if SubTree data is not NULL
        shared_ptr<BinaryNode<ItemType>> leftPtr = subTreePtr->getLeftChildPtr(); // object variable declaration and initialization (left pointer)
        shared_ptr<BinaryNode<ItemType>> rightPtr = subTreePtr->getRightChildPtr(); // object variable declaration and initialization (right pointer)
        
        if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr)){ // if statement that checks value condition of pointers (if left > right)
            rightPtr = balAdd(rightPtr , newNodePtr); // adds newNode data into right pointer
            subTreePtr->setRightChildPtr(rightPtr); // subtree for right pointer
        }
        else{ // (if right > left)
            leftPtr = balAdd(leftPtr, newNodePtr); // adds newNode data into left pointer
            subTreePtr->setLeftChildPtr(leftPtr); // subtree for leftpointer
        }
        
        return subTreePtr; // return new data modification of BNT (new SubTree)
    }
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::moveValUp(shared_ptr<BinaryNode<ItemType>> subTreePtr){ // method moveValUp() definition
    shared_ptr<BinaryNode<ItemType>> leftPtr = subTreePtr->getLeftChildPtr();  // object variable declaration and initialization (left pointer)
    shared_ptr<BinaryNode<ItemType>> rightPtr = subTreePtr->getRightChildPtr();  // object variable declaration and initialization (right pointer)

    int leftHeight = getHeightHelper(leftPtr); // variable declaration and initializaiton (height of left pointer)
    int rightHeight = getHeightHelper(rightPtr); // variable declaration and initializaiton (height of right pointer)

    if (leftHeight > rightHeight){ // if statement that checks value condition of pointer heights (if left > right)
        // Algorithm to move left pointer upwards //

        subTreePtr->setItem(leftPtr->getItem());
        leftPtr = moveValUp(leftPtr);
        subTreePtr->setLeftChildPtr(leftPtr);

        return subTreePtr; // return new data modification of BNT (new SubTree)
    }
    else{ // (if right > left)
        if (rightPtr != nullptr){ // if statement (checks to see if right pointer data is not equal to NULL)
            // Algorithm to move right pointer upwards //

            subTreePtr->setItem(rightPtr->getItem());
            rightPtr = moveValUp(rightPtr);
            subTreePtr->setRightChildPtr(rightPtr);

            return subTreePtr; // return new data modification of BNT (new SubTree)
        }
        else{ // (if right pointer data is equal to NULL)
            return nullptr; // return NULL pointer
        }
    }
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& success){ // method removeValue() definition
    if(subTreePtr == nullptr){ // if statement (checks to see if SubTree value is NULL)
        return subTreePtr; // return current state of SubTree (current data)
    }
    
    if (subTreePtr->getItem() == target){ // if statement (checks to see if SubTree data equal to passed value/variable data (target))
        subTreePtr = moveValUp(subTreePtr); // call method moveValUp()
        success = true; // boolean success assigned to 'true'

        return subTreePtr; // return new state of SubTree (new data)
    }
    else{ // (if SubTree data is not equal to target data)
        shared_ptr<BinaryNode<ItemType>> targetNodePtr = removeValue(subTreePtr->getLeftChildPtr(), target, success); // object variable declaration and initialization (target node pointer [left])
        subTreePtr->setLeftChildPtr(targetNodePtr); // assigning left child pointer data to target data

        if (!success){ // if statement (not successful)
            targetNodePtr = removeValue(subTreePtr->getRightChildPtr(), target, success); // object variable declaration and initialization (target node pointer [right])
            subTreePtr->setRightChildPtr(targetNodePtr);  // assigning right child pointer data to target data
        }
        
        return subTreePtr; // return new state of SubTree (new data)
    }
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::findNode(shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType& target, bool& success) const{ // method findNode() definition
    if (treePtr == nullptr){ // if statement (checks to see if Tree value is NULL)
        return treePtr; // return current state of SubTree (current data)
    }

    if (treePtr->getItem() == target){ // if statement (checks to see if Tree data equal to passed value/variable data (target))
        success = true;  // boolean success assigned to 'true'

        return treePtr; // return current state of SubTree (current data)
    }
    else{ // (if Tree data is not equal to target data)
        shared_ptr<BinaryNode<ItemType>> targetNodePtr = findNode(treePtr->getLeftChildPtr(), target, success); // object variable declaration and initialization (target node pointer [left]); position

        if (!success){ // if statement (not successful)
            targetNodePtr = findNode(treePtr->getRightChildPtr(), target, success); // object variable declaration and initialization (target node pointer [right]); position
        }
        
        return targetNodePtr; // return found Node (target node data)
    }
}

template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::copyTree(const shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const{ // method copyTree() definition
    shared_ptr<BinaryNode<ItemType>> newTreePtr; // object variable declaration and initialization (NEW TREE)
   
    if (oldTreeRootPtr != nullptr){ // if statement (checks to see if original root pointer value is NOT NULL)
        // Copying Data between BS Trees //

        newTreePtr = make_shared<BinaryNode<ItemType>>(oldTreeRootPtr->getItem(), nullptr, nullptr); // assigning object variable to shared

        newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr())); // assinging left child pointer data of OldTree to NewTree
        newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr())); // assigning right child pointer of OldTreee to NewTree
    }
    
    return newTreePtr; // returning NewTree data (copied)
}

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(shared_ptr<BinaryNode<ItemType>> subTreePtr){ // method destroyTree() definition
    if (subTreePtr != nullptr){ // if statement (checks to see if subTree value is NOT NULL)
        destroyTree(subTreePtr->getLeftChildPtr()); // destroy left child pointer data of SubTree
        destroyTree(subTreePtr->getRightChildPtr()); // destroy right child pointre data of SubTree

        subTreePtr.reset(); // reset SubTree State
    }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const{ // method preorder() definition
    if (treePtr != nullptr){ // if statement (checks to see if Tree value is NOT NULL)
        ItemType chosenItem = treePtr->getItem(); // object variable declaration and initialization (Item Data)
        visit(chosenItem); // visit() variable data

        preorder(visit, treePtr->getLeftChildPtr()); // preorder() left child pointer data
        preorder(visit, treePtr->getRightChildPtr()); // preorder() right child pointer data

        cout << treePtr->getItem() << " "; // cout preorder() Tree Data (Sorted)
    }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const{ // method inorder() definition
    if (treePtr != nullptr){ // if statement (checks to see if Tree value is NOT NULL)
        inorder(visit, treePtr->getLeftChildPtr()); // inorder() left child pointer data

        ItemType chosenItem = treePtr->getItem(); // object variable declaration and initialization (Item Data)
        visit(chosenItem); // visit() variable data

        inorder(visit, treePtr->getRightChildPtr()); // inorder() right child pointer data

        cout << treePtr->getItem() << " "; // cout inorder() Tree Data (Sorted)
    }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const{ // method postorder() definition
    if (treePtr != nullptr){ // if statement (checks to see if Tree value is NOT NULL)
        postorder(visit, treePtr->getLeftChildPtr()); // postorder() left child pointer data
        postorder(visit, treePtr->getRightChildPtr()); // postorder() right child pointer data

        ItemType chosenItem = treePtr->getItem(); // object variable declaration and initialization (Item Data)
        visit(chosenItem); // visit() variable data

        cout << treePtr->getItem() << " "; // cout inorder() Tree Data (Sorted)
    }
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(){} // constructor definition

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem):rootPtr(make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr)){} // parameterized constructor definition

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem, const shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr, const shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr):rootPtr(make_shared<BinaryNode<ItemType>>(rootItem, copyTree(leftTreePtr->rootPtr), copyTree(rightTreePtr->rootPtr))){} // parameterized constructor definition

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr){ // copy constructor definititon
    rootPtr = copyTree(treePtr.rootPtr); // root pointer data is assinged to the root data of copied tree (copying data)
}

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree(){ // destructor definition
    destroyTree(rootPtr); // call destroyTree(): deletes root pointer (eliminates rest of Tree data)
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const{ // method isEmpty() definition
    return rootPtr == nullptr; // checks to see if root pointer of tree equals NULL: if so, it is empty (true)
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType &anEntry) const{ // method contains() definition
    bool isSuccessful = false; // boolean variable declaration and initalization (false): success?

    findNode(rootPtr, anEntry, isSuccessful); // call findNode() to look for data

    return isSuccessful; // return boolean isSucessful
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const{ // method getHeight() definition
    return getHeightHelper(rootPtr); // return height of BNT
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const{ // method getNumberOfNodes definition
    return getNumberOfNodesHelper(rootPtr); // returns numbere of nodes within BNT
}

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newItem){ // method setRootData() definition
    if (isEmpty()){ // if statement(checks to see if BNT is empty)
        rootPtr = make_shared<BinaryNode<ItemType>>(newItem, nullptr, nullptr); // assigns new root pointer
    }
    else{ // (if BNT is NOT EMPTY)
        rootPtr->setItem(newItem); // assigns old root pointer to passed value/variable data
    }
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData){ // method add() definition
    shared_ptr<BinaryNode<ItemType>> newNodePtr = make_shared<BinaryNode<ItemType>>(newData); // object variable declaration and initialization (new node pointer data)

    rootPtr = balAdd(rootPtr, newNodePtr); // new node pointer data added to BNT

    return true; // return true (successful)
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& target){ // method remove() definition
    bool isSuccessful = false; // boolean variable declaration and initalization (false): success?

    rootPtr = removeValue(rootPtr, target, isSuccessful); // call removeValue() to remove target data

    return isSuccessful; // return boolean isSucessful
}

template<class ItemType>
void BinaryNodeTree<ItemType>::clear(){ // method clear() definition
    destroyTree(rootPtr); // call destroyTree() in order to clear BNT (proper memory deallocation)

    rootPtr.reset(); // reset root pointer
}

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const{ // method preorderTraverse() definition
    preorder(visit, rootPtr); // preorder() algorithm/function
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const{ // method inorderTraverse() definition
    inorder(visit, rootPtr); // inorder() algorithm/function
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const{ // method postorderTraverse() definition
    postorder(visit, rootPtr); // postorder() algorithm/function
}  

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException){ // method getEntry() definition
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
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PrecondViolatedExcept){ // method getRootData() definition
    if (isEmpty()){ // if statement(checks to see if BNT is empty)
        throw PrecondViolatedExcept("Error! getRootData() method was called with an empty tree."); // cout prompt (ERROR)
    } 
       
    return rootPtr->getItem(); // return root pointer data of BNT
}

template<class ItemType>
BinaryNodeTree<ItemType> &BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree<ItemType> &rightHandSide){ // assingment operator definition
    if (!isEmpty()){ // if statement (checks to see if BNT is NOT EMPTY)
        clear(); // call clear() to empty BNT
    }

    this = copyTree(&rightHandSide); // copied tree is copied into BNT
    
    return *this; // return new BNT data
}

#endif // BINARY_NODE_TREE_H