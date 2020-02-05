// Abraham Meza //
// CS 302 - Project 2 //

// This file is a program that utilizes rand() methods in order to create random integer files, in conjunction to file manipulation, prescribed in Project 2 of CS-302 //

// header files //

#include <iostream>
#include <fstream>
#include <ctime>

// namespace declarations //

using namespace std;

const int NumofSorts = 10; // const for NumofSorts that user wants to execute

int randomGen(int minimum, int maximum); // function protorype (picks out an integer in between min and max)

int main(void){ // main program:
    srand(time(NULL)); // srand()

    int minimum = 0; // variable declaration and initialization
    int maximum = 0; // variable declaration and initialization
    int count = 0; // variable declaration and initialization

    string filename; // string declaration

  	cout << "\n" <<
            "//////////////////////////////////////\n" <<
            "/////  Random Generator Program  /////\n" <<
            "//////////////////////////////////////" << endl << endl; // test label design


    cout << "Welcome to the Random Generator Program!!" << endl << "Please enter the following data:" << endl << endl; // cout labeling

    cout << "Please establish the range in which to choose from." << endl << endl; // cout labeling

    cout << "Minimum Number of the Range: "; // cout labeling
    cin >> minimum; // cin user input (minimum)
    cout << endl; // cout formatting

    cout << "Maxiumum Number of the Range: "; // cout labeling
    cin >> maximum; // cin user input (maximum)
    cout << endl; // cout formatting

    cout << "How many random integers would you like to generate? "; // cout labeling
    cin >> count; // cin user input (count)
    cout << endl; // cout formatting

    ofstream outputStream; // declares file manipulation

    for (int i = 0; i < NumofSorts; i++){
        filename = "Data/Unsorted/DataUnsorted_" + to_string(count) + "_" + to_string(i + 1) + ".txt"; // creates new file (string label)

        outputStream.open(filename); // opens file indicated by program (output file)

        for (int j = 0; j < count; j++) { // for loop that executes (count) number of times to generate a random integer value into output file
            outputStream << randomGen(minimum, maximum); // export randomGen() number to output file
            
            if (j != count){
                outputStream << endl; // output file formatting (organization)
            }
        }

        outputStream.close(); // close opened (output) file

        cout << "Random Generator successful! Please look for '" << filename << "' in your folder." << endl << endl; // cout confirmation (lets user know which file the numbers were exported to)
    }

    return 0; // end of program
}

int randomGen(int minimum, int maximum){ // randomGen() method definition
    int range = maximum - minimum; // variable declaration and initialization (range)

    return (rand() % range) + minimum; // returns random integer value between range
}