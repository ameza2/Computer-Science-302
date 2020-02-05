// Abraham Meza //
// CS 302 - Project 5 //

#ifndef LEFT_LEANING_RED_BLACK_TREE
#define LEFT_LEANING_RED_BLACK_TREE

// header file(s) //

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

// custom header file(s) //

#include "RedBlackNode.h"

// namespace declaration(s) //

using namespace std;

// Function Protoype(s) //

string appString(const Color color); // appString(): appends string

// Class Skeleton(s) //

template<class ItemType>
void debugNode(const RedBlackNode<ItemType> *node); // templated class method: debugNode()

template<class ItemType>
class LeftLeaningRedBlackTree{ // templated class declaration
    private:
        RedBlackNode<ItemType> *rootPtr; // object pointer declaration (rootPtr)

    protected:
        //------------------------------------------------------------
        // Protected Utility Methods Section:
        // Recursive helper methods for the public methods.
        //------------------------------------------------------------
        // Places a given new node at its proper position in this binary
        // search tree.
        //------------------------------------------------------------

        RedBlackNode<ItemType> *placeNode(RedBlackNode<ItemType> *subTreePtr, RedBlackNode<ItemType> *newNode); // object method(): placing node into Tree enviroment 

        RedBlackNode<ItemType> *insertRec(RedBlackNode<ItemType> *subtree, RedBlackNode<ItemType> *node); // object method(): inserting new specified key
        RedBlackNode<ItemType> *deleteRec(RedBlackNode<ItemType> *subtree, const ItemType& target); // object method(): deleting specified key

        RedBlackNode<ItemType>* Rotate_Left(RedBlackNode<ItemType> *node); // object method(): rotating left node
        RedBlackNode<ItemType>* Rotate_Right(RedBlackNode<ItemType> *node); // object method(): rotating right node

        RedBlackNode<ItemType>* findMin(RedBlackNode<ItemType>* node); // object method(): finding the minimum value of LLRBT (node)
        RedBlackNode<ItemType>* deleteMin(RedBlackNode<ItemType>* node); // object method(): deleting the minimum value of the Tree enviroment (node)

        RedBlackNode<ItemType>* moveRed_Left(RedBlackNode<ItemType>* node); // object method(): move red node leftwards
        RedBlackNode<ItemType>* moveRed_Right(RedBlackNode<ItemType>* node); // object method(): move red node rightwards

        RedBlackNode<ItemType>* fixUp(RedBlackNode<ItemType>* node); // object method(): fixUp() method; clean processing errors

        int getNodeHeight(RedBlackNode<ItemType> *subTreePtr) const; // method getNodeHeight(): get specified node height (integer)

        bool isRed(RedBlackNode<ItemType> *node) const; // method isRed(): checks to see if specifed node is red (boolean)
        void switchColors(RedBlackNode<ItemType> *node); // method switchColors(): switches color of the specified node (Black -> Red, Red -> Black)

        void preorder(RedBlackNode<ItemType> *subTreePtr) const; // method preorder(): provides preorder transversal of LLRBT
        void inorder(RedBlackNode<ItemType> *subTreePtr) const; // method inorder(): provides inorder transversal of LLRBT
        void postorder(RedBlackNode<ItemType> *subTreePtr) const; // method postorder(): provides postorder transversal of LLRBT

    public:
        //------------------------------------------------------------
        // Constructor and Destructor Section.
        //------------------------------------------------------------

        LeftLeaningRedBlackTree(); // default constructor 
        
        //------------------------------------------------------------
        // Public Methods Section.
        //------------------------------------------------------------

        int getHeight() const; // method getHeight(): provides the height of LLRBT (int)

        bool add(const ItemType& newData); // boolean expression; method add(): checks to see if addition of value to LLRBT was a success
        bool remove(const ItemType& data); // boolean expression; method remove(): checks to see if removal of value from LLRBT was a success

        //------------------------------------------------------------
        // Public Traversals Section.
        //------------------------------------------------------------

        void preorderTraverse() const; // method preorder(): provides preorder transversal of LLRBT
        void inorderTraverse() const; // method inorder(): provides inorder transversal of LLRBT
        void postorderTraverse() const; // method postorder(): provides postorder transversal of LLRBT
}; // end of class declaration

template<class ItemType>
void debugNode(const RedBlackNode<ItemType> *node){ // method debugNode() definition
    if (node != nullptr){ // if statement (checks to see if node data is not NULL)
        cout << "Number: " << node->getItem() << endl << "Color: " << appString(node->getColor()) << endl << endl; // cout confirmation (Node data and Node color)
    }
}

template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::placeNode(RedBlackNode<ItemType> *subTreePtr, RedBlackNode<ItemType> *newNode){ // method placeNode() definition
    RedBlackNode<ItemType>* tempPtr; // object variable declaration and initialization (temp pointer)

    if (subTreePtr == nullptr){ // if statement (checks to see if SubTree Pointer data is NULL)
        return newNode; // return newNode data
    }
    else if (subTreePtr->getItem() > newNode->getItem()){ // else if statement (checks to see if SubTree Pointer data is greater than NewNode data)
        tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNode); // newNode data (leftChildPtr) assigned to tempPtr
        subTreePtr->setLeftChildPtr(tempPtr); // subtree for new leftChildPtr (tempPtr)
    } 
    else{ // else statement (if SubTree Pointer data is less than NewNode data)
        tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNode);  // newNode data (rightChildPtr) assigned to tempPtr
        subTreePtr->setRightChildPtr(tempPtr); // subtree for new rightChildPtr (tempPtr)
    }

    return subTreePtr; // return new data modification of LLRBT (new SubTree)
}

template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::insertRec(RedBlackNode<ItemType> *subtree, RedBlackNode<ItemType> *node){ // method InsertRec() definition
    if (subtree == nullptr){ // if statement (checks to see if SubTree data is NULL)
        return node; // return node data
    }

    if (node->getItem() < subtree->getItem()){ // if statement (checks to see if node data is less than SubTree data)
        subtree->setLeftChildPtr(insertRec(subtree->getLeftChildPtr(), node)); // subtree for new leftChildPtr (node)
    } 
    else{ // if statement (if node data is greater than SubTree data)
        subtree->setRightChildPtr(insertRec(subtree->getRightChildPtr(), node)); // subtree for new rightChildPtr (node)
    }

    if (isRed(subtree->getRightChildPtr()) && !isRed(subtree->getLeftChildPtr())){ // if statement (checks to see that rightChildPtr is red and leftChildPtr is not red)
        subtree = Rotate_Left(subtree); // Left Rotation (subtree)
    }

    if (isRed(subtree->getLeftChildPtr()) && isRed(subtree->getLeftChildPtr()->getLeftChildPtr())){ // if statement (checks to see that leftChildPtr data is red, and checks to see that the leftChildPtr of the leftChildPtr is red)
        subtree = Rotate_Right(subtree); // Right Rotation (subtree)
    }

    if (isRed(subtree->getLeftChildPtr()) && isRed(subtree->getRightChildPtr())){ // if statement (checks to see that leftChildPtr is red and rightChildPtr is red)
        switchColors(subtree); // switches node colors; both ChildPtrs (Left/Right) will go from Red -> Black 
    }

    return subtree; // return new data modification of LLRBT (new SubTree)
}

template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::deleteRec(RedBlackNode<ItemType> *subtree, const ItemType &target){ // method deleteRec() definition
    if (target < subtree->getItem()){ // if statement (checks to see that passed data is less than SubTree data)
        if (subtree->getLeftChildPtr() != nullptr){ // if statement (checks to see leftChildPtr data is not NULL)
            if (!isRed(subtree->getLeftChildPtr()) && !isRed(subtree->getLeftChildPtr()->getLeftChildPtr())){ // if statement (checks to that leftChildPtr is not red, and checks to see that the leftChildPtr of the leftChilldPtr is not red)
                subtree = moveRed_Left(subtree); // call moveRed_Left(): move red node leftwards
            }
            
            subtree->setLeftChildPtr(deleteRec(subtree->getLeftChildPtr(), target)); // subtree for new leftChildPtr; delete target 
        }
    } 
    else{ // if statement (if target data is greater than SubTree data)
        if (isRed(subtree->getLeftChildPtr())){ // if statement (checks to see that leftChildPtr is red)
            subtree = Rotate_Right(subtree); // Right Rotation (subtree)
        }

        if (target == subtree->getItem() && subtree->getRightChildPtr() == nullptr){ // if statement (checks to see that target data is equal to SubTree data and that rightChildPtr is NULL)
            delete subtree; // delete subtree
            return nullptr; // return NULL (pointer)
        }

        if (subtree->getRightChildPtr() != nullptr){ // if statement (checks to see that rightChildPtr is not NULL)
            if (!isRed(subtree->getRightChildPtr()) && !isRed(subtree->getRightChildPtr()->getLeftChildPtr())){ // if statement (checks to see that rightChildPtr is not red, and checks to see that the leftChidPtr of the RightChildPtr is not red )
                subtree = moveRed_Right(subtree); // call moveRed_Right(): move red node rightwards
            }

            if (target == subtree->getItem()){ // if statement (checks to see that target data is equal to SubTree data)
                subtree->setItem(findMin(subtree->getRightChildPtr())->getItem()); // SubTree Item data = Minimum of LLRBT
                subtree->setRightChildPtr(deleteMin(subtree->getRightChildPtr())); // subtree for new rightChildPtr; delete minimum 
            }
            else{ // if statement (if target data is not equal to SubTree data)
                subtree->setRightChildPtr(deleteRec(subtree->getRightChildPtr(), target)); // subtree for new rightChildPtr; delete target 
            }
        }
    }

    return fixUp(subtree); // return fixUp() cleanup of SubTree; new data modification of LLRBT (new SubTree)
}

template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::Rotate_Left(RedBlackNode<ItemType> *node){ // method Rotate_Left() definition
    RedBlackNode<ItemType>* temp = node->getRightChildPtr(); // object variable declaration and initialization (temp pointer)

    node->setRightChildPtr(temp->getLeftChildPtr()); // leftChildPtr (temp node) data is assigned to rightChildPtr data (node)
    temp->setLeftChildPtr(node); // node data is assigned to leftChildPtr (temp node)

    temp->setColor(node->getColor()); // temp color set to node color
    node->setColor(RED); // node color set to RED 

    return temp; // return temp data
}

template<class ItemType>
RedBlackNode<ItemType>*  LeftLeaningRedBlackTree<ItemType>::Rotate_Right(RedBlackNode<ItemType> *node){ // method Rotate_Right definition
    RedBlackNode<ItemType>* temp = node->getLeftChildPtr(); // object variable declaration and initialization (temp pointer)

    node->setLeftChildPtr(temp->getRightChildPtr()); // rightChildPtr (temp node) data is assigned to leftChildPtr data (node)
    temp->setRightChildPtr(node);  // node data is assigned to rightChildPtr (temp node)

    temp->setColor(node->getColor()); // temp color set to node color
    node->setColor(RED); // node color set to RED 

    return temp; // return temp data
}

template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::findMin(RedBlackNode<ItemType>* node){ // method findMin() definition
    while (node->getLeftChildPtr() != nullptr){ // while loop (continues until leftChildPtr data is NULL)
        node = node->getLeftChildPtr(); // leftChildPtr data is assigned to node data
    }

    return node; // return node data (last leftChildPtr)
}

template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::deleteMin(RedBlackNode<ItemType>* node){ // method deleteMin() definition
    if (node->getLeftChildPtr() == nullptr){ // if statement (checks to see that leftChildPtr data is equal to NULL)
        delete node; // delete node 
        return nullptr; // return NULL (pointer)
    }

    if (!isRed(node->getLeftChildPtr()) && !isRed(node->getLeftChildPtr()->getLeftChildPtr())){ // if statement (checks to see that leftChildPtr is not red, and checks to see that leftChildPtr of leftChildPtr is not red)
        node = moveRed_Left(node); // call moveRed_Left(): move red node leftwards
    }

    node->setLeftChildPtr(deleteMin(node->getLeftChildPtr())); // node for new leftChildPtr; delete minimum 

    return fixUp(node);  // return fixUp() cleanup of node; new data modification of LLRBT (new node)
}

template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::moveRed_Left(RedBlackNode<ItemType>* node){ // method moveRed_Left() definition
    switchColors(node); // call switchColors() method: switch node color (i.e. Black -> Red, Red -> Black)

    if (node->getRightChildPtr() != nullptr && isRed(node->getRightChildPtr()->getLeftChildPtr())){ // if statement (checks to see that rightChidPtr is not NULL, and checks to see that leftChildPtr of rightChildPtr is red)
        node->setRightChildPtr(Rotate_Right(node->getRightChildPtr())); // node for new rightChildPtr; Right Rotation (node)
        node = Rotate_Left(node); // Left Rotation (node)

        switchColors(node); // call switchColors() method: switch node color (i.e. Black -> Red, Red -> Black)
    }

    return node; // return node data
}

template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::moveRed_Right(RedBlackNode<ItemType>* node){ // method moveRed_Right() definition
    switchColors(node); // call switchColors() method: switch node color (i.e. Black -> Red, Red -> Black)

    if (node->getLeftChildPtr() != nullptr && isRed(node->getLeftChildPtr()->getLeftChildPtr())){ // if statement (checks to see that leftChildPtr is not NULL, and checks to see that leftChildPtr of leftChildPtr is red)
        node = Rotate_Right(node); // Right Rotation (node)

        switchColors(node); // call switchColors() method: switch node color (i.e. Black -> Red, Red -> Black)
    }

    return node; // return node data
}

template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::fixUp(RedBlackNode<ItemType>* node){ // method fixUp() definition
    if (isRed(node->getRightChildPtr())){ // if statement (checks to see that rightChildPtr is red)
        node = Rotate_Left(node); // Left Rotation (node)
    }

    if (isRed(node->getLeftChildPtr()) && isRed(node->getLeftChildPtr()->getLeftChildPtr())){ // if statement (checks to see that leftChildPtr is red, and checks to see that leftChildPtr of leftChildPtr is red)
        node = Rotate_Right(node); // Right Rotation (node)
    }

    if (isRed(node->getLeftChildPtr()) && isRed(node->getRightChildPtr())){ // if statement (checks to see that leftChildPtr is red, and checks to see that rightChildPtr is red)
        switchColors(node); // call switchColors() method: switch node color (i.e. Black -> Red, Red -> Black)
    }

    return node; // return node data
}

template<class ItemType>
int LeftLeaningRedBlackTree<ItemType>::getNodeHeight(RedBlackNode<ItemType> *subTreePtr) const{ // method getNodeHeight() definition
    if (subTreePtr == nullptr){ // if statement (checks to see that SubTree pointer is NULL: Treee is Empty)
        return 0;
    } 
    else{ // if statement (if SubTree pointer is not NULL: Tree is Not Empty)
        int leftHeight = getNodeHeight(subTreePtr->getLeftChildPtr()); // leftHeight of LLRBT (integer)
        int rightHeight = getNodeHeight(subTreePtr->getRightChildPtr()); // rightHeight of LLRBT (integer)
    
        return max(leftHeight, rightHeight) + 1; // return height of LLRBT; make up for (0) node layer: Max (Height) + 1
    }
}

template<class ItemType>
bool LeftLeaningRedBlackTree<ItemType>::isRed(RedBlackNode<ItemType> *node) const{ // method isRed() definition
    if (node != nullptr){ // if statement (checks to see that node data is not NULL)
        return node->getColor() == RED; // return boolean; checks to see if node color is RED
    }

    return false; // return boolean; null nodes are BLACK
}

template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::switchColors(RedBlackNode<ItemType> *node){ // method switchColors() definition
    node->switchColor(); // call switchColor() method: switch node color (i.e. Black -> Red, Red -> Black)

    node->getLeftChildPtr()->switchColor(); // switch leftChildPtr color (i.e. Black -> Red, Red -> Black)
    node->getRightChildPtr()->switchColor(); // switch rightChildPtr color (i.e. Black -> Red, Red -> Black)
}

template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::preorder(RedBlackNode<ItemType> *subTreePtr) const{ // method preorder() definition
    if (subTreePtr == nullptr){ // if statement (checks to see that SubTree Pointer is NULL)
        return; // return (exit)
    }

    cout << subTreePtr->getItem() << "(" << appString(subTreePtr->getColor()) << ") "; // cout confirmation (append format)

    preorder(subTreePtr->getLeftChildPtr()); // preorder() left child pointer data
    preorder(subTreePtr->getRightChildPtr()); // preorder() right child pointer data
}

template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::inorder(RedBlackNode<ItemType> *subTreePtr) const{ // method inorder() definition
    if (subTreePtr == nullptr){ // if statement (checks to see that SubTree Pointer is NULL)
        return; // return (exit)
    }

    inorder(subTreePtr->getLeftChildPtr()); // inorder() left child pointer data
    
    cout << subTreePtr->getItem() << "(" << appString(subTreePtr->getColor()) << ") "; // cout confirmation (append format)

    inorder(subTreePtr->getRightChildPtr()); // inorder() right child pointer data
}

template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::postorder(RedBlackNode<ItemType> *subTreePtr) const{ // method postorder() definition
    if (subTreePtr == nullptr){ // if statement (checks to see that SubTree Pointer is NULL)
        return; // return (exit)
    }

    postorder(subTreePtr->getLeftChildPtr()); // postorder() left child pointer data
    postorder(subTreePtr->getRightChildPtr()); // inorder() right child pointer data

    cout << subTreePtr->getItem() << "(" << appString(subTreePtr->getColor()) << ") "; // cout confirmation (append format)
}

template<class ItemType>
LeftLeaningRedBlackTree<ItemType>::LeftLeaningRedBlackTree() : rootPtr(nullptr) {} // default constructor definition

template<class ItemType>
int LeftLeaningRedBlackTree<ItemType>::getHeight() const{ // method getHeight() definition
    return getNodeHeight(rootPtr); // return height of LLRBT
}

template<class ItemType>
bool LeftLeaningRedBlackTree<ItemType>::add(const ItemType &newData){ // method add() definition
    RedBlackNode<ItemType> *newNodePtr = new RedBlackNode<ItemType>(newData); // object variable declaration and initialization (new node pointer data)

    rootPtr = insertRec(rootPtr, newNodePtr); // call insertRec() to add specified data; new node pointer data added to LLRBT

    rootPtr->setColor(BLACK); // set new node color (BLACK)

    return true; // return boolean true
}

template<class ItemType> // double check //
bool LeftLeaningRedBlackTree<ItemType>::remove(const ItemType &data){ // method remove() definition
    rootPtr = deleteRec(rootPtr, data); // call deleteRec() to remove specified data; target node removed from LLRBT

    return true; // return boolean true
}

template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::preorderTraverse() const{ // method preorderTraverse() definition
    cout << "Preorder Traversal: "; // cout confirmation
    preorder(rootPtr); // preorder() algorithm/function
    cout << endl; // cout formatting
}

template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::inorderTraverse() const{ // method inorderTraverse() definition
    cout << "Inorder Traversal: "; // cout confirmation
    inorder(rootPtr); // inorder() algorithm/function
    cout << endl; // cout formatting
}

template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::postorderTraverse() const{ // method postorderTraverse() definition
    cout << "Postorder Traversal: "; // cout confirmation
    postorder(rootPtr); // postorder() algorithm/function
    cout << endl; // cout formatting
}

// Prototype Definitions //

string appString(const Color color){ // function appString() definition
    if (color){ // if statement (checks node color for black)
        return "B"; // if node color is black; append 'B'
    }

    return "R"; // if node color is red; append 'R'
}

#endif // LEFT_LEANING_RED_BLACK_TREE_H