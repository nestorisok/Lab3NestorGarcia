﻿//// interpreter for simplified infix expression with {+, -, *, / } operations;
//// keyboard input, single digit numbers only and no spaces are allowed;
//// compile: $> g++ prog1.cpp
//// run with: 2+3*4/2+3+4*2
#include <cstdlib> //for atoi()
#include <iostream>

#include <string>
#include <fstream> // file reading

using namespace std;

// using file input

int exp(), term(), fact(), exp2(int), term2(int), fact2(int), myChar();

string prog; //string for reading 1-line input expression (program)
int indexx = 0; //global index for program string

int main(int argc, const char** argv)
{
	string tempstring;
	char tempchar;

	ifstream myfile;
	myfile.open("myProg.txt");

	while (myfile >> tempchar) {		// while it is not the end of file
		prog += tempchar;				// we insert char into string
	}

	myfile.close();					// we then close the file

	cout << "\nEquation = " << prog << endl;
 	cout << "\nResult = " << exp() << endl;



   }

// exp() returns value from exp2(term())
int exp()		// exp: tail-end recursion to call our non-terminals
{

	return exp2(term());	// if exp is called, we goto exp2 with our term
}

// term() returns value from term2(fact())
int term() 	// term: using tail-end recursion to call non-terminals
{

	return term2(fact2(fact())); // term calls fact() -> fact2() -> term2()
}


// fact() checks to see if there is a left parantheses first
int fact()
{

		if (prog.at(indexx) == '(')			// if left parantheses at indexx
		{
				indexx++;					// we incremenet to get next char
				int result = exp();			// keep result of exp() in result
				if (prog.at(indexx) == ')')	// checks to see if the indexx is sitting at right parantheses
				{
					indexx++;				// if so, we increment to next char
				}
				return result;				// we return result to fact2() which is nested in term2()

		}
		
			return fact2(atoi(&prog.at(indexx++)));		// we check the next char for its value (PEMDAS)

}


// using input 'inp' we make our local variable 'result' be 'inp'
// if the current indexx is less than our prog.length then it is not at the end of string
// we get a single char from program string and make it local variable char 'a'
// if 'a' is '+' we have 'result' value change to exp2(result + term())
// if 'a' is '-' we have 'result' value change to exp2(result - term())
// after all the calls, the 'result' is returned

int exp2(int inp)		// implements right-recursive form to get our 'inp' by
{						// calling exp2 either adding or subtracting our result and our 'term'

	int result = inp;
	if (indexx < prog.length()) //if not the end of program string
	{
		char a = prog.at(indexx++); //get one chr from program string
		if (a == '+')
			result = exp2(result + term()); //handles t+t
		else if (a == '-')
			result = exp2(result - term()); //handles t-t
		else
			indexx--;		// if none of these, we go back one step

	}
	return result;
}


// using input 'inp' we make it a local variable 'result' be 'inp'
// if our 'indexx' is less than the length of 'prog' then it is not the end of string, so we continue
// we then get char 'a' to be a single char from the string
// if 'a' is '*' we have 'result' value change to term2(result * term())
// if 'a' is '/' we have 'result' value change to term2(result / term())
// if 'a' is either '+' or '-' then we go back one position
// after all these we return our result

int term2(int inp)
{

	int result = inp;
	if (indexx < prog.length()) //if not the end of program string
	{
		char a = prog.at(indexx++); //get one chr from program string
		if (a == '*')
			result = term2(result * fact()); //handles consecutive * operators
		else if (a == '/')
			result = term2(result / fact()); //handles consecutive / operators
		else //if + or -, get back one position
			indexx--;
	}
	return result;
}

// fact2() does our power, if our current character is a '^', we make our result
// be the base to our next character, and so forth, nested so it can recursively check
// for the upcoming characters
int fact2(int inp)
{
	int result = inp;
	if (indexx < prog.length())
	{
		char a = prog.at(indexx++);  
		if (a == '^')
		{
			result = fact2(pow(result, fact()));  // Correctly handle right-associative
		}
		else
			indexx--;  // Step back if not '^'

	}
	return result;
}

//
//int myChar()
//{
//
//	cout << "myNum\n";
//
//	char a = prog.at(indexx++); //get one chr from program string
//
//	return atoi(&a); //converts a char to a numeric number and return
//
//
//}