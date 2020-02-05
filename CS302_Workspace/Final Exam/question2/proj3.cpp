// Abraham Meza //
// CS 302 - Project 3 //

// This file is a program that creates a Binary Search Tree from a randomized integer file, while also expressing specified Tree elements such as height and traversals, prescribed in Project 3 of CS-302 //

// header files //

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// custom header files //

#include "BinarySearchTree.h"

// namespace declarations //

using namespace std;

// Const Variables: utilized for Random Integer Generator //

const int NumOfVals = 100; // number of integers
const int MinOfVals = 1; // minimum value of integers
const int MaxOfVals = 200; // maximum value eof integers

std::vector<int> SortedTree; // vector declaration (BST): Sorted Tree

// Function Protoypes //

int randomGen(int minimum, int maximum); // randomGen(): picks out an integer in between min and max

void show(int& dataItem); // show(): displays the items within the BST: vector<int> (Sorted Tree)

int main(void){ // main program
	srand(time(NULL)); // srand()
	
	BinarySearchTree<int> Tree; // BinarySearchTree vector (Tree) declaration
	
	int random_number = 0; // variable declartion and initializtion
	string filename; // string declaration

	ofstream outputSteam; // declares file manipulation
	filename = "BST_Random_Numbers.txt"; // creates new file (string label)

	cout << "\n" <<
            "////////////////////////////////////////\n" <<
            "/////  Binary Search Tree Program  /////\n" <<
            "////////////////////////////////////////" << endl << endl; // test label design

	outputSteam.open(filename); // opens file indicated by program (output file)

	for (int i = 0; i < NumOfVals; i++){ // for loop (iterations for number of integers desired within BST)
		random_number = randomGen(MinOfVals, MaxOfVals); // assigning random_number with randomly generatedd number from function prototype

		outputSteam << random_number << endl; // export random_number data to output file

		Tree.add(random_number); // addiing random_number data to BST structure
	}

	outputSteam.close(); // close opened (output) file

	cout << "Binary Search Tree Height: " << Tree.getHeight() << endl; // cout confirmation (results): exports height of BST to terminal
	cout << endl; // cout formatting

	cout << "Pre-order Traverse: " << endl; // cout confirmation
	Tree.preorderTraverse(show); // preorderTraverse() method (Sorted BST displayed to terminal)
	cout << endl << endl; // cout formatting

	cout << "In-order Traverse: " << endl; // cout confirmation
	Tree.inorderTraverse(show); // inorderTraverse() method (Sorted BST displayed to terminal)
	cout << endl << endl; // cout formatting

	cout << "Post-order Traverse: " << endl; // cout confirmation
	Tree.postorderTraverse(show); // postorderTraverse() method (Sorted BST displayed to terminal)
	cout << endl << endl; // cout formatting

	return 0; // end program
}

// Function Prototype Definitions //

int randomGen(int minimum, int maximum){ // randomGen() method definition
    int range = maximum - minimum; // variable declaration and initialization (range)

    return (rand() % range) + minimum; // returns random integer value between range
}

void show(int& dataItem){ // display() method definition
	cout << dataItem << " "; // cout confirmation: prints dataItem data from Sorted BST (Tree)

	SortedTree.push_back(dataItem); // push_back() method for dataItem data (NEXT ITEM)
}
