// Abraham Meza //
// This file is a program that utilizes postfix operators in conjunctiton to linked-list stacks prescribed in Project 2 of CS-302 //

// Header  Files //
#include <stdexcept>
#include <iostream>
#include <cmath> // '^' - exponential function symbol

using namespace std; // namespace declaration

// Custom Header Files //
#include "Stack.h"
#include "StackLinked.h"

float postfix(const string &expression); // function prototype

int main(void){
	///////////////////////////////////////////////////
	//// Main Program resembles delimiters.cs 	   ////
	////									       ////
	//// Modified slightly for postfix utilization ////
	///////////////////////////////////////////////////

	string arithmetic; // string declaration (arithmetic)
	char character; // characterr declaration (character)

  	cout << "\n" <<
            "////////////////////////////////\n" <<
            "/////  Postfix Arithmetic  /////\n" <<
            "////////////////////////////////" << endl << endl; // test label design

	while(cin){ 
		cout << "Enter a postfix arithmetic operation (please include whitespace in-between characters): " << endl;
		
		arithmetic = "";
		cin.get(character);

		while(cin && character != '\n'){
			arithmetic = arithmetic + character;
			cin.get(character);
		}

		if(!cin){
			break;
		}

		cout << endl << "The result is: " << postfix(arithmetic) << endl << endl; // cout confirmation (result of postfix operator)
	}

	return 0; // end of program
}

float postfix(const string &expression){
	StackLinked <char> character; // Stack that records the expression in postfix form (guinea pig data)
	StackLinked <float> flo; // Stack that has results after all conversions and calculations

	char conv; // Character that converts data through conditional statements
	float operand1 = 0, operand2 = 0; // Declares operands (1 and 2)

	for (int i = expression.size(); i >= 0; i--){ // for loop for stack manipualtion and navigation
		if (expression[i] != ' '){ // if statement that removes whitespace
			character.push(expression[i]); // only push() (es) valid characters
		}
	}

	while (!character.isEmpty()){  // while loop that assures that stack has been scanned/modified completely
		conv = character.pop(); // pops first element for conversion

		if (conv >= '0' && conv <= '9') { // evaluates numbers between 0-9 (checks)
			if (conv == '0'){ // push (0)
				flo.push(0);
			}
			if (conv == '1'){ // push(1)
				flo.push(1);
			}
			if (conv == '2'){ // push (2)
				flo.push(2);
			}
			if (conv == '3'){ // push(3)
				flo.push(3);
			}
			if (conv == '4'){ // push(4)
				flo.push(4);
			}
			if (conv == '5'){ // push(5)
				flo.push(5);
			}
			if (conv == '6'){ // push(6)
				flo.push(6);
			}
			if (conv == '7'){ // push(7)
				flo.push(7);
			}
			if (conv == '8'){ // push(8)
				flo.push(8);
			}
			if (conv == '9'){ // push(9)
				flo.push(9);
			}
		}

		else if (conv == '+' || conv == '-' || conv == '*' || conv == '/' || conv == '^'){ // evaluates operations (+, -, *, /)
			////////////////////////////////////////////////////
			// Format is located within homework instructions //
			////////////////////////////////////////////////////

			if (conv == '+'){
				operand1 = flo.pop();
				operand2 = flo.pop();
				flo.push(operand1 + operand2); // (+) operation
			}
			if (conv == '-'){
				operand1 = flo.pop();
				operand2 = flo.pop();
				flo.push(operand2 - operand1); // (-) operation
			}
			if (conv == '*'){
				operand1 = flo.pop();
				operand2 = flo.pop();
				flo.push(operand1 * operand2); // (*) operation
			}
			if (conv == '/'){
				operand1 = flo.pop();
				operand2 = flo.pop();
				flo.push(operand2 / operand1); // (/) operation
			}
			if (conv == '^'){
				operand1 = flo.pop();
				operand2 = flo.pop();
				flo.push(powf(operand2,operand1));
			}
		}
	}

	return flo.pop(); // returns evaluated and finalized result (one number)
}