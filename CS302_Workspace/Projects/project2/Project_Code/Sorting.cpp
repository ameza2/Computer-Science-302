// Abraham Meza //
// CS 302 - Project 2 //

// This file is a program that utilizes sorting aglorithms to sort integer files, while testing their efficiencies, prescribed in Project 2 of CS-302 //

// In order to switch from unsorted files to sorted files, and vice versa, user must go into program and modify readFile name to "Data/Sorted/..." or "Data/Unsorted/..." //

// header files //

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

// custom header files //

#include "SelectionSort.h"
#include "MergeSort.h"

// namespace declarations //

using namespace std;
using namespace chrono;

const int NumofSorts = 10; // const for NumofSorts that user wants to execute

int main(void){ // main program

    // Sorting Variables //

    int comps = 0, swaps = 0, average_comps = 0, average_swaps = 0, total_comps = 0, total_swaps = 0; // variable declaration and initialization (sorting) (swaps and comps (total and average))
    double total_time = 0, average_time = 0, currentTime = 0; // variable declaration and initialization (time (total and average))

    // User Variables //

    int quantity = 0, userSort = 0, choice = 0; // variable declaration and initialization (user sort input)

    // Other Variables //
    bool on = true; // bool declaration and initialization (used as on/off switch for program) 
    clock_t time_sort; // clock declaration
    string filename;  // string declaration
    ifstream inputStream; // declares file manipulation

    cout << "\n" <<
            "/////////////////////////////////////\n" <<
            "/////  General Sorting Program  /////\n" <<
            "/////////////////////////////////////" << endl << endl; // test label design

    cout << "Welcome to the General Sorting Program!!" << endl << "This sorting program utilizes Selection Sort and Merge Sort to organize random integer files, while also measuring their efficiecies." << endl << endl; // cout labeling

    cout << "Please note, you must have a pre-made integer .txt file within the source code folder beforehand. Or, you may excecute RandomGen.cpp for a sample file." << endl << endl; // cout labeling

    cout << "Please enter the following data:" << endl << endl; // cout labeling; 

    cout << "Please indicate the number of integers you would like to organize: "; // cout labeling
    cin >> quantity; // user input
    cout << endl; // formatting

    cout << "Which sorting method would you like to utilize?" << endl << endl; // cout labeling

    while (on == true){ // switch (on)

        // Menu Selections //

        cout << "Sorting Option Menu:" << endl;
        cout << "[1] Selection Sort" << endl;
        cout << "[2] Merge Sort" << endl;
        
        cout << endl << "Please enter a menu option: "; // user input that declares menu selection
        cin >> userSort; // user input
        cout << endl; // formatting

        cout << "Would you like to export the sorted file(s)? (1 - Yes, 2 - No) "; // user input that declares if(export_file)
        cin >> choice; // user input
        cout << endl; // formatting

        while(choice != 1 && choice != 2){ // while loop (check)
            cout << "Invalid Option!!" << endl; // cout confirmation (Error)

            cout << "Would you like to export the sorted file(s)? (1 - Yes, 2 - No) "; // user input that declares if(export_file)
            cin >> choice; // user input
            cout << endl; // formatting
        }

        switch(userSort){ // switch statement
            case 1:
            {
                ////////////////////////////////
                //       Selection Sort       //
                ////////////////////////////////

                SelectionSort ss(quantity); // number of integer values (maxSize)
                
                cout << "\n" <<
                        "///////////////////////////////////////\n" <<
                        "/////  Selection Sorting Results  /////\n" <<
                        "///////////////////////////////////////" << endl << endl; // test label design

                for (int i = 0; i < NumofSorts; i++){ // for loop that runs sorting algorithm NumofSorts of times in order to get an accurate rate of efficiency
                    ss.readFile("Data/Unsorted/DataUnsorted_" + to_string(quantity) + "_" + to_string(i + 1) + ".txt"); // opening/reading program input file
                    filename = "Data/Unsorted/DataUnsorted_" + to_string(quantity) + "_" + to_string(i + 1) + ".txt"; // string initialization: new file (string label)

                    time_sort = clock(); // clock start
                    ss.sort(comps, swaps); // executing selection sort
                    time_sort = clock() - time_sort; // number of ticks during period of clock start/end

                    if (choice == 1){ // if statement (if user wants to export sorted data)
                        ss.writeFile(filename); // exporting current array data to designted file
                    }

                    currentTime = ((double)time_sort/CLOCKS_PER_SEC); // to keep track of time for each iteration

                    cout << "[" << i + 1 << "] "
                        << "SECONDS: " << setprecision(8) << currentTime << " \t" << "COMPARISONS: " << setprecision(10) << comps << " \t" <<  "SWAPS: " << setprecision(10) << swaps << endl; // cout confirmation (results)

                    total_swaps += swaps; // to keep track of total swaps for all sorts combined (average)
                    total_comps += comps; // to keep track of total comparisons for all sorts combined (average)
                    total_time += ((double)time_sort/CLOCKS_PER_SEC); // to keep track of total time for all sorts combined (average)

                    swaps = 0; // reset swaps for new data 
                    comps = 0; // reset comparisons for new data
                }

                    cout << endl; // formatting

                    if (choice == 1){
                        cout << "Data Transfer successful! Please look for the sorted files in your folder!" << endl << endl; // cout confirmation (lets user know which file the numbers were exported to)
                    }

                    average_time = (total_time / NumofSorts); // average time for sorting (selection)
                    average_comps = (total_comps / NumofSorts); // average comparisons for sorting (selection)
                    average_swaps = (total_swaps / NumofSorts); // average swaps for sorting (selection)

                    cout << "The sorting took: " << average_time << " seconds on average for " << NumofSorts << " different sorts." << endl; // cout confirmation
                    cout << "The sorting made: " << average_comps << " comparisons on average for " << NumofSorts << " different sorts." << endl; // cout confirmation
                    cout << "The sorting made: " << average_swaps << " swaps on average for " << NumofSorts << " different sorts." << endl; // cout confirmation
                    cout << endl; // formatting

                    on = false; // switch (off)
                    break;
            }
            case 2:
            {
                ////////////////////////////
                //       Merge Sort       //
                ////////////////////////////

                MergeSort ms(quantity); // number of integer values (maxSize)

                cout << "\n" <<
                        "////////////////////////////////////\n" <<
                        "/////  Merge Sorting Results  /////\n" <<
                        "///////////////////////////////////" << endl << endl; // test label design

                for (int i = 0; i < NumofSorts; i++){ // for loop that runs sorting algorithm NumofSorts of times in order to get an accurate rate of efficiency
                    ms.readFile("Data/Unsorted/DataUnsorted_" + to_string(quantity) + "_" + to_string(i + 1) + ".txt"); // opening/reading program input file
                    filename = "Data/Unsorted/DataUnsorted_" + to_string(quantity) + "_" + to_string(i + 1) + ".txt"; // string initialization: new file (string label)

                    time_sort = clock(); // clock start
                    ms.merge_sort(ms.getArray(), 0, ms.getSize() - 1, comps, swaps); // executing merge sort
                    time_sort = clock() - time_sort; // number of ticks during period of clock start/end

                    if (choice == 1){ // if statement (if user wants to export sorted data)
                        ms.writeFile(filename); // exporting current array data to designted file
                    }

                    currentTime = ((double)time_sort/CLOCKS_PER_SEC); // to keep track of time for each iteration

                    cout << "[" << i + 1 << "] "
                        << "SECONDS: " << setprecision(8) << currentTime << " \t" << "COMPARISONS: " << setprecision(10) << comps << " \t" <<  "SWAPS: " << setprecision(10) << swaps << endl; // cout confirmation (results)

                    total_swaps += swaps; // to keep track of total swaps for all sorts combined (average)
                    total_comps += comps; // to keep track of total comparisons for all sorts combined (average)
                    total_time += ((double)time_sort/CLOCKS_PER_SEC); // to keep track of total time for all sorts combined (average)

                    swaps = 0; // reset swaps for new data 
                    comps = 0; // reset comparisons for new data
                }

                cout << endl; // formatting

                if (choice == 1){
                    cout << "Data Transfer successful! Please look for the sorted files in your folder!" << endl << endl; // cout confirmation (lets user know which file the numbers were exported to)
                }

                average_time = (total_time / NumofSorts); // average time for sorting (selection)
                average_comps = (total_comps / NumofSorts); // average comparisons for sorting (selection)
                average_swaps = (total_swaps / NumofSorts); // average swaps for sorting (selection)

                cout << "The sorting took: " << average_time << " seconds on average for " << NumofSorts << " different sorts." << endl; // cout confirmation
                cout << "The sorting made: " << average_comps << " comparisons on average for " << NumofSorts << " different sorts." << endl; // cout confirmation
                cout << "The sorting made: " << average_swaps << " swaps on average for " << NumofSorts << " different sorts." << endl; // cout confirmation
                cout << endl; // formatting

                on = false;
                break;
            }
            default: // Prevents user from entering anything else except the menu options.
            {
                cout << "Invalid Option!" << endl << endl; // cout confirmation (invalid)
                break;
            }
        }
    }

    return 0; // end of program
}