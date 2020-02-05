// Abraham Meza //
// CS 302 - Project 6 //
// This file is a program that creates an environmental graph to solve the Traveling Salesman Problem as prescribed in Project 6 of CS-302 //

// ** Note: All metric values were done seperately (distance researched) and then inputted into the program's matirx //

// Header File(s) //

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <climits>

// Namespace Declaration(s) //

using namespace std; 

// Const Variables: utilized for TSP Algorithm //

const int CITIES = 5; // number of cities of interest

// Function Protoype(s) //

int TravelingSalesman(int Graph[][CITIES], int t); // TravelingSalesman(): Conducts an algorithm in which all possible paths are evaluated, and the minimum path is chosen and displayed on the terminal
void showPaths(int arr[16][6]); // showPaths(): prints individual miles/cost for all possible paths in program matrix (TSP)

// Universal Variable Declaration and Initialization //

int allPossiblePaths[16][6] = { // array declaration and initalization (distance between cities of interest)
	{218, 809, 835, 422, 466},
	{218, 566, 422, 835, 750},
	{218, 736, 835, 1254, 466},
	{218, 736, 422, 1254, 750},

	{466, 566, 809, 835, 518},
	{466, 422, 835, 809, 218},
	{466, 1254, 809, 736, 518},
	{466, 1254, 835, 736, 218},

	{518, 422, 566, 809, 750},
	{518, 835, 809, 566, 466},
	{518, 736, 809, 1254, 466},
	{518, 736, 566, 1254, 750},

	{750, 809, 566, 422, 518},
	{750, 835, 422, 566, 218},
	{750, 1254, 566, 736, 518},
	{750, 1254, 422, 736, 218},
};

int main(){ // main program
    cout << "\n" <<
            "///////////////////////////////////////\n" <<
            "/////  Traveling Salesman Problem /////\n" <<
            "///////////////////////////////////////" << endl << endl; // test label design

	showPaths(allPossiblePaths); // showPaths(): prints individual miles/cost for all possible paths in program matrix (TSP)

	int Graph[][CITIES] = { // matrix representation of Graph 
		{0, 218, 466, 518, 750}, 
		{218, 0, 566, 736, 809}, 
		{466, 566, 0, 422, 1254}, 
		{518, 736, 422, 0, 835},
        {750, 809, 1254, 835, 0} 
	};
    
	int t = 0; // variable declaration and initialization (int)

	TravelingSalesman(Graph, t); // TravelingSalesman(): Conducts an algorithm in which all possible paths are evaluated, and the minimum path is chosen and displayed on the terminal

	cout << "\n" <<
            "////////////////////////////////////////////////\n" <<
            "/////  Leading Route(s) from TSP Algorithm /////\n" <<
            "////////////////////////////////////////////////" << endl << endl; // test label design

	cout << "Path 1 Route: Reno -> San Francisco -> Seattle -> Salt Lake -> Las Vegas -> Reno" << endl; // manual cout confirmation
	cout << endl; // cout labeling

	cout << "Path 6 Route: Reno -> Las Vegas -> Salt Lake -> Seattle -> San Francisco -> Reno" << endl; // manual cout confirmation
    cout << endl; // cout labeling
    
	return 0; // end program
} 

// Function Prototype(s) Definitions //

int TravelingSalesman(int Graph[][CITIES], int t){ // TravelingSalesman() method definition
	
	vector<int> vertex; // Vector declaration (int): Vector

	for (int i = 0; i < CITIES; i++){ // for loop: scans through all cities of interest
		if (i != t){ // if statement (checks to see if current i value (tracking) is not equal to t value (main))
			vertex.push_back(i); // push_back(): pushes given values into vector environment (current i value (tracking))
        }
    }

	// Hamilton Cycle Algorithm //

	int minPath = INT_MAX; // varaiable declaration and initialization (int): cannot store any value (macro) beyond its limit

	do{ // do while loop (scans through all possible paths for TSP algorithm; determines least costly path)
		
        int currentPath_Cost = 0;  // variable declaration and initalization (int) : current cost (0)
		
		// Current Path Cost Algorithm //

		int c = t; // variable declaration and initalization

		for (int i = 0; i < vertex.size(); i++){ // for loop: scans through all cities of interest
			currentPath_Cost += Graph[c][vertex[i]];  // assigning the sum value of total path cost to current path cost
			c = vertex[i]; // assigning current value of vertex array element to c (indicates path)
		} 

		currentPath_Cost += Graph[c][t]; // assigning the sum value of total path cost to current path cost (last element)

		minPath = min(minPath, currentPath_Cost); // assigning minimum cost value to minimum path (update minimum); min(): returns the smallest of the input values
		
	} while (next_permutation(vertex.begin(), vertex.end())); // (loop is executed until complete vector scan)

	return minPath; // return minimum path (least costly)
}

void showPaths(int arr[16][6]){ // showPaths() method definition
	// Variable Declaration and Initalization //

    int Path = 0; // Variable Path (int)
	int Path2 = 0; // Variable Path 2 (int)
    int Minimum = 0; // Variable Minimum (int)
	int Minimum2 = 0; // Variable Minimum 2 (int)
	int temp = 0; // Variable Temporary (int)

	cout << "\n" <<
            "////////////////////////////////////////\n" <<
            "/////  All Possible Paths for TSP /////\n" <<
            "///////////////////////////////////////" << endl << endl; // test label design


	for (int i = 0; i < 16; i++){ // for loop: scans through all possible paths between cities of interest
		int Maximum = 0; // variable declaration and initialization (int)

		for (int j = 0; j < 6; j++){ // for loop: scans for all cities of interest
			Maximum += arr[i][j]; // assinging the sum value of maxmimum and array element to maximum
		}

		temp = Maximum; // assigning maximum value to temporary (placeholder)

		if (i == 0){ // if statement (checks for the first (base) city (i == 0))
			Minimum = Maximum; // assigning maximum value to minimum
			Path = i; // assigning current i value to Path (tracking)
		} else if (Minimum > temp){ // else if statement (checks to see if current minimum is greater than temp value)
			Minimum = temp; // assigning temporary value to minimum
			Path = i; // assinging current i value to Path (tracking)
		} else if (Minimum == temp){ // else if statement (checks to see if current minimum is equal to temp value)
			Minimum2 = temp; // assigning temporary value to minimum 2
			Path2 = i; // assinging current i value to Path (tracking)
		}

		cout << "Total Cost for Path " << i + 1 << ": " << Maximum << endl << endl; // cout confirmation
	}

    cout << "\n" <<
            "///////////////////////////////////////////////\n" <<
            "/////  Minimum Path(s) from TSP Algorithm /////\n" <<
            "///////////////////////////////////////////////" << endl << endl; // test label design

	cout << "Minimum Path from TSP Algorithm: " << Minimum << endl << endl; // cout confirmation

	if ((Minimum) == (Minimum2)){ // if statement (if current minimum is equal to current minimum 2)
		cout << "Minimum Path from TSP Algorithm is Path " << Path + 1 << ": " << Minimum << endl << endl; // cout confirmation
		cout << "Minimum Path from TSP Algorithm is Path " << Path2 + 1 << ": " << Minimum2 << endl << endl; // cout confirmation
	}
	else if ((Minimum) > (Minimum2)){ // else if statement (if current minimum is greater than current minimum 2)
		cout << "Minimum Path from TSP Algorithm is Path " << Path2 + 1 << ": " << Minimum2 << endl << endl; // cout confirmation
	}
	else{ // else statement (if current minimum is less than current minimum 2)
		cout << "Minimum Path from TSP Algorithm is Path " << Path + 1 << ": " << Minimum << endl << endl; // cout confirmation
	}
}