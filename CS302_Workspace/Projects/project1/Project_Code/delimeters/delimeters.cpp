// Abraham Meza //
// This file is a program that utilizes delimeters in conjunctiton to linked-list stacks prescribed in Project 2 of CS-302 //

//--------------------------------------------------------------------
//
//   delimiters.cpp
//
//--------------------------------------------------------------------

#include <iostream>

#include "config.h"

#if LAB6_TEST1
#   include "StackLinked.h"
#else
#   include "StackArray.h"
#endif

//--------------------------------------------------------------------

bool delimitersOk ( const string &expression );

//--------------------------------------------------------------------

int main()
{
    string inputLine;            // Input line
    char   ch;                   // Holding pen for input chars

    cout << "This program checks for properly matched delimiters."
         << endl;

    while( cin )
    {
        cout << "Enter delimited expression (<EOF> to quit) : "
             << endl;

        // Read in one line
        inputLine = "";
        cin.get(ch);
        while( cin && ch != '\n' )
        {
            inputLine = inputLine + ch;
            cin.get(ch);
        }

        if( ! cin )              // Reached EOF: stop processing
            break;
    
        if ( delimitersOk (inputLine) )
            cout << "Valid" << endl;
        else
            cout << "Invalid" << endl;
    }

    return 0;
}

//--------------------------------------------------------------------
// delimitersOk: the function that students must implement for 
//    Programming Exercise 3.
// Note: we used the term "braces" to describe '[' and ']'. It would
//    have been better to use the term "brackets". The program can be
//    easily modified to process any set of matching delimiters.
//--------------------------------------------------------------------

// Insert your delimitersOk function below

bool delimitersOk(const string& expression){ // delimitersOk method definition
    StackLinked<string> str; // declares templated string stack

    for (int i = 0; i < expression.size(); i++){ // for loop that scans through expression

        ///////////////////////////////////////////////////////////////
        // if statements that organize delimiters based on its forms //
        ///////////////////////////////////////////////////////////////

        if (expression[i] == '('){ 
            str.push("(");
        }
        if (expression[i] == ')'){
            str.push(")");
        }
        if (expression[i] == '['){
            str.push("[");
        }
        if (expression[i] == ']'){
            str.push("]");
        }
        if (expression[i] == '{'){
            str.push("{");
        }
        if (expression[i] == '}'){
            str.push("}");
        }
    }

    int parentCount = 0, bracketCount = 0, curlyCount = 0; // symbol counters (corresponding symbols) declaration and initialization

    string character = "0"; // string declaration and initialization
    character = str.pop(); // assigned to pop() value (symbol)

    ////////////////////////////////////////////////////////////////////
    // if statements that check for first element delimiter (opening) //
    ////////////////////////////////////////////////////////////////////

    if (character[0] == '('){
        return false; // opening symbol
    }
    if (character[0] == ')'){
        parentCount--; // ending symbol
    }
    if (character[0] == '['){
        return false; // opening symbol
    }
    if (character[0] == ']'){
        bracketCount--; // ending symbol
    }
    if (character[0] == '{'){
        return false; // opening symbol
    }
    if (character[0] == '}'){
        curlyCount--; // ending symbol
    }

    while(!str.isEmpty()){ // while loop that assures that stack is being processed (not empty)
        character = str.pop(); // assigned to pop() value (symbol)

        /////////////////////////////////////////////////////////////////
        // if statements that check for opening and closing delimiters //            
        //                                                             //
        // increments and decrements counter accordingly               //
        // (opening = ++, closing = --)                                //
        //                                                             //
        /////////////////////////////////////////////////////////////////
    
        if (character[0] == '('){
            parentCount++; // opening symbol
        }
        if (character[0] == ')'){
            parentCount--; // closing symbol
        }
        if (character[0] == '['){
            bracketCount++; // opening symbol
        }
        if (character[0] == ']'){
            bracketCount--; // closing symbol
        }
        if (character[0] == '{'){
            curlyCount++; // opening symbol
        }
        if (character[0] == '}'){
            curlyCount--; // closing symbol
        }
    }

    ////////////////////////////////////////////////////////////////////
    // if statements that check for first element delimiter (closing) //            
    ////////////////////////////////////////////////////////////////////

    if (character[0] == ')'){
        return false;
    }
    if (character[0] == ']'){
        return false;
    }
    if (character[0] == '}'){
        return false;
    }

    if (parentCount == 0 && bracketCount == 0 && curlyCount == 0){ // valid = all counters added = 0
        return true;
    }
    else{ // invalid = all counters added != 0
        return false;
    }
}