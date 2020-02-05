// Abraham Meza //
// CS 302 - Project 5 //

// This file is a program that creates a Left Leaning Red Black Tree from given random integers, while also expressing specified methods, such as add() and remove(). Given particular methods, the program maintains the proper tree format as prescribed in Project 5 of CS-302 (Balanced BST) //

// header file(s) //

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

// custom header file(s) //

#include "LeftLeaningRedBlackTree.h"

// namespace declaration(s) //

using namespace std;

// Const Variables: utilized for Random Integer Generator //

const int NumOfVals = 10; // number of integers
const int MinOfVals = 1; // minimum value of integers
const int MaxOfVals = 100; // maximum value of integers

// Function Protoype(s) //

int randomGen(int minimum, int maximum); // randomGen(): picks out an integer in between min and max

int main(){ // main program
    srand(time(NULL));

    cout << "\n" <<
            "////////////////////////////////////////////////////////\n" <<
            "/////  Left Leaning Red Black Tree Data Structure  /////\n" <<
            "////////////////////////////////////////////////////////" << endl; // test label design

    LeftLeaningRedBlackTree<int> tree; // Vector declaration (int): LLRBT Vector

    int Insertion, Deletion; // variable declaration (int): Insertion (add node) || Deletion (remove node)

    for (int i = 0; i < NumOfVals; i++){ // for loop: generates random integers, given NumofVals, then adds the values into the vector
        Insertion = randomGen(MinOfVals, MaxOfVals); // assigns the randomly generated integer into indicated variable (Insertion)

        if (i == 3) { // if statement (compares iteration (i) to an indicated number; keeps track of integer value for future deletion); i == 3: fourth randomly generated integer (4-1)
            Deletion = Insertion; // assigning current Insertion data to Deletion data
        }

        cout << endl << "Inserting Process: " << Insertion << endl; // cout confirmation
        tree.add(Insertion); // add(): adds given data (value) into LLRBT environment 
        tree.preorderTraverse(); // preorderTraverse(): provides preorder state of current LLRBT environment
    }

    cout << endl << "Deletion Process: " << Deletion << endl; // cout confirmation
    tree.remove(Deletion); // remove(): removes given data (value) from LLRBT environment
    tree.preorderTraverse(); // preorderTraverse(): provides preorder state of current LLRBT environment
    
    cout << endl; // cout formatting

    return 0; // end program
}

int randomGen(int minimum, int maximum){ // randomGen() method definition
    int range = maximum - minimum; // variable declaration and initialization (range)

    return (rand() % range) + minimum; // returns random integer value between range
}