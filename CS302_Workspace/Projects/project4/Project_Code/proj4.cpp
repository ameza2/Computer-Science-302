// Abraham Meza //
// CS 302 - Project 4 //

// This file is a program that creates a Heap Data Structure from given random integers, while also expressing specified Heap methods, such as push_heap(), pop_heap(), and sort_heap(), prescribed in Project 4 of CS-302 //

// header files //

#include <iostream>
#include <vector>
#include <algorithm>

// namespace declarations //

using namespace std;

// Const Variables: utilized for Random Integer Generator //

const int NumOfVals = 100; // number of integers
const int MinOfVals = 1; // minimum value of integers
const int MaxOfVals = 200; // maximum value of integers

// Function Protoypes //

int randomGen(int minimum, int maximum); // randomGen(): picks out an integer in between min and max
int meanVec(vector<int> &heapVec); // meanVec(): provides the mean integer value of the vector data
void showVec(vector<int> &heapVec, const char *label); // showVec(): displays the current data within the vector: vector<int> (heapVec)

int main() { // main program
    srand(time(NULL));

    cout << "\n" <<
            "/////////////////////////////////\n" <<
            "/////  Heap Data Structure  /////\n" <<
            "/////////////////////////////////" << endl << endl; // test label design

    ////////////////////////////////////////////////////////
    // 1. Make a vector consisting of 100 random integers //
    ////////////////////////////////////////////////////////

    vector<int> heapVec; // Vector declaration (int): Heap Vector

    for (int i = 0; i < NumOfVals; i++){ // for loop: generates random integers, given NumofVals, then pushes the values into the vector
        heapVec.push_back(randomGen(MinOfVals, MaxOfVals)); // push_back(): pushes given values into vector environment (random)
    }

    make_heap(heapVec.begin(), heapVec.end()); // make_heap(): rearranges elements within vector to create a Heap; highest element pointed by first
    showVec(heapVec, "The current heap (Random Integers): "); // showVec(): displays current state of vector (Random Integers)

    int vecMean = meanVec(heapVec); // int declaration and initialization (vecMean); meanVec(): holds current mean value of vector
    
    cout << "The mean of the current heap is: " << vecMean << endl; // cout confirmation (mean)
	cout << "The maximum element of the current heap is: " << heapVec.front() << endl; // cout confirmation (max element); no need for maxElement function as Heaps always put the highest element first
	cout << endl; // cout formatting

    ////////////////////////////////////////////////////////
    // 2. Add a new value that is the mean of the random  //
    //    values you created in the previous step.        //
    //    Floor the value if needed.                      //
    ////////////////////////////////////////////////////////
    
    push_heap(heapVec.begin(), heapVec.end()); // push_heap(): increases size by 1
    heapVec.push_back(vecMean); // push_back(): pushes given values into vector environment (mean); push_back() value added to the end of the Heap
    showVec(heapVec, "The current heap w/ added mean value: "); // showVec(): displays current state of vector (Heap w/ mean)

    vecMean = meanVec(heapVec); // assigning new value to integer variable (vecMean); meanVec(): holds current mean value of vector

    cout << "The mean of the current heap is: " << vecMean << endl; // cout confirmation (mean)
	cout << "The maximum element of the current heap is: " << heapVec.front() << endl; // cout confirmation (max element); no need for maxElement function as Heaps always put the highest element first
	cout << endl; // cout formatting

    ///////////////////////////////////////////////
    // 3. Delete the maximum element of the heap //
    ///////////////////////////////////////////////

    pop_heap(heapVec.begin(), heapVec.end()); // pop_heap(): rearranges the elements so heap is shortened by 1; places top element (max) at the back of the heap
    heapVec.pop_back(); // pop_back(): removes last element in the vector; reduces size by 1
    showVec(heapVec, "The current heap w/ maximum element deleted: "); // showVec(): displays current state of vector (Heap w/ max removed)

    vecMean = meanVec(heapVec); // assigning new value to integer variable (vecMean); meanVec(): holds current mean value of vector

    cout << "The mean of the current heap is: " << vecMean << endl; // cout confirmation (mean)
	cout << "The maximum element of the current heap is: " << heapVec.front() << endl; // cout confirmation (max element); no need for maxElement function as Heaps always put the highest element first
	cout << endl; // cout formatting

    ///////////////////////
    // 4. Sort the heap. //
    ///////////////////////

    sort_heap(heapVec.begin(), heapVec.end()); // sort_heap(): sorts the elements of the heap in ascending order
    showVec(heapVec, "The current sorted heap (Ascending Order): "); // showVec(): displays current state of vector (Sorted Heap)

    vecMean = meanVec(heapVec); // assigning new value to integer variable (vecMean); meanVec(): holds current mean value of vector

    cout << "The mean of the current heap is: " << vecMean << endl; // cout confirmation (mean)
	cout << "The maximum element of the current heap is: " << heapVec.back() << endl; // cout confirmation (max element); no need for maxElement function as Heaps always put the highest element first
	cout << endl; // cout formatting

    return 0; // end program
}

// Function Prototype Definitions //

int randomGen(int minimum, int maximum){ // randomGen() method definition
    int range = maximum - minimum; // variable declaration and initialization (range)

    return (rand() % range) + minimum; // returns random integer value between range
}

int meanVec(vector<int> &heapVec){ // meanVec() method definition
    int sum = 0; // int declaration and initialization (sum); 

    for (int i = 0; i < heapVec.size(); i++){ // for loop: scans through all vector data (size()) and adds the data together
        sum += heapVec[i]; // assigning new value to integer variable (sum); sum = sum + data
    }
    int mean = sum / heapVec.size(); // int declaration and initialization (mean); mean = sum / SizeOfVector

    return mean; // returns integer value (mean)
}

void showVec(vector<int> &heapVec, const char *label){ // showVec() method definition
    cout << label << endl; // cout confirmation (labeling)

    for (int i = 0; i < heapVec.size(); i++) {  // for loop: scans through all vector data (size()) and prints the data to terminal
        cout << heapVec[i] << " "; // cout confirmation (data)
    }
    cout << endl << endl; // cout labeling
}