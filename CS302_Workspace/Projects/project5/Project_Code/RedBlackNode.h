// Abraham Meza //
// CS 302 - Project 5 //

#ifndef RED_BLACK_NODE
#define RED_BLACK_NODE

// header file(s) //

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

// namespace declaration(s) //

using namespace std;

// Class Skeleton(s) //

enum Color {RED, BLACK}; // Color List (enum)

template<class ItemType>
class RedBlackNode{ // templated class decaration
    private:
        ItemType item; // object declaration (item)

        RedBlackNode<ItemType> *leftChildPtr; // object pointer declaration (leftChildPtr)
        RedBlackNode<ItemType> *rightChildPtr; // object pointer declaration (rightChildPtr)
        RedBlackNode<ItemType> *parentPtr; // object pointer declaration (parentPtr)

        Color color; // object declaration (color)

    public:
        //------------------------------------------------------------
        // Constructor and Destructor Section.
        //------------------------------------------------------------

        RedBlackNode(const ItemType &anItem); // parameterized constructor

        //------------------------------------------------------------
        // Getter/Setter Methods Section.
        //------------------------------------------------------------

        RedBlackNode<ItemType> *getLeftChildPtr() const; // object method getLeftChildPtr(): get the data of the specifed leftChildPtr
        RedBlackNode<ItemType> *getRightChildPtr() const; // object method getRightChildPtr(): get the data of the specifed rightChildPtr
        RedBlackNode<ItemType> *getParentPtr() const; // object method getParentPtr(): get the data of the specifed ParentPtr

        void setLeftChildPtr(RedBlackNode<ItemType> *leftPtr); // method setLeftChildPtr(): assigns the specifed data to an existing variable (leftPtr)
        void setRightChildPtr(RedBlackNode<ItemType> *rightPtr); // method setRightChildPtr(): assigns the specifed data to an existing variable (rightPtr)
        void setParentPtr(RedBlackNode<ItemType> *parentPtr); // method setParentPtr(): assigns the specifed data to an existing variable (parentPtr)

        ItemType getItem() const; // object method getItem(): gets the data (value) of a specified Item (NODE)
        Color getColor() const; // object method getColor(): gets the data (color) of a specified Item (NODE)

        void setItem(const ItemType &anItem); // method setItem(): assigns the specifed data (value) to an existing variable (NODE)
        void setColor(const Color newColor); // method setItem(): assigns the specifed data (color) to an existing variable (NODE)

        //------------------------------------------------------------
        // Public Methods Section.
        //------------------------------------------------------------
        
        void switchColor(); // method switchColor(): switches the color of a specified Item (NODE); newColor derived from enum Color options (BLACK/RED)
}; // end of class declaration

template<class ItemType>
RedBlackNode<ItemType>::RedBlackNode(const ItemType &anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr), parentPtr(nullptr), color(RED) {} // paramterized constructor definition

template<class ItemType>
RedBlackNode<ItemType>* RedBlackNode<ItemType>::getLeftChildPtr() const{ // method getLeftChildPtr() definition
    return leftChildPtr; // return leftChidPtr data
}

template<class ItemType>
RedBlackNode<ItemType>* RedBlackNode<ItemType>::getRightChildPtr() const{ // method getRightChildPtr() definition
    return rightChildPtr; // return rightChidPtr data
}

template<class ItemType>
RedBlackNode<ItemType>* RedBlackNode<ItemType>::getParentPtr() const{ // method getParentPtr() definition
    return parentPtr; // return parentPtr data
}

template<class ItemType>
void RedBlackNode<ItemType>::setLeftChildPtr(RedBlackNode<ItemType> *leftPtr){ // method setLeftChildPtr() definition
    leftChildPtr = leftPtr; // assigns the passed data (leftPtr) to a variable (leftChildPtr)
}

template<class ItemType>
void RedBlackNode<ItemType>::setRightChildPtr(RedBlackNode<ItemType> *rightPtr){ // method setRightChildPtr() definition
    rightChildPtr = rightPtr; // assigns the passed data (rightPtr) to a variable (rightChildPtr)
}

template<class ItemType>
void RedBlackNode<ItemType>::setParentPtr(RedBlackNode<ItemType> *parent){ // method setParentPtr() definition
    parentPtr = parent; // assigns the passed data (parent) to a variable (parentPtr)
}

template<class ItemType>
ItemType RedBlackNode<ItemType>::getItem() const{ // method getItem() definition
    return item; // return item data
}

template<class ItemType>
Color RedBlackNode<ItemType>::getColor() const{ // method getColor() definition
    return color; // return color data
}

template<class ItemType>
void RedBlackNode<ItemType>::setItem(const ItemType &anItem){ // method setItem() definition
    item = anItem; // assigns the passed data (anItem) to a variable (item)
}

template<class ItemType>
void RedBlackNode<ItemType>::setColor(const Color newColor){ // method setColor() definition
    color = newColor; // assigns the passed data (newColor) to a variable (color)
}

template<class ItemType>
void RedBlackNode<ItemType>::switchColor(){ // method switchColor() definition
    if (color == RED){ // if statement (checks to see that color is red)
        color = BLACK; // if node color is red, then assign BLACK to color

        return; // return (exit)
    }

    color = RED; // if node color is black, then assign RED to color
}

#endif // RED_BLACK_NODE_H