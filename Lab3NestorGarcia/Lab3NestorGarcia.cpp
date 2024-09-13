//// interpreter for simplified infix expression with {+, -, *, / } operations;
//// keyboard input, single digit numbers only and no spaces are allowed;
//// compile: $> g++ prog1.cpp
//// run with: 2+3*4/2+3+4*2
#include <cstdlib> //for atoi()
#include <iostream>

#include <string>
#include <fstream> // file reading

using namespace std;

// using file input

int exp(), term(), fact(), exp2(int), term2(int), fact2(int), myNum();

string prog; //string for reading 1-line input expression (program)
int indexx = 0; //global index for program string

int main(int argc, const char** argv)
{
	string tempstring;
	char tempchar;

	ifstream myfile;
	myfile.open("myprog.txt");

	while (!myfile.eof()) {		// while it is not the end of file

		myfile.get(tempchar);	// we get the char from file
		if (tempchar != ' ') {	// if the char is not a space,
			tempstring += tempchar;	// we insert it into the string
		}

		prog = tempstring;			// prog now contains tempstring

	}
	myfile.close();				// we then close the file


	//cout << ">";				// original code
	//cin >> prog;				// user inserts prog

	cout << "\nresult= " << exp() << endl;



}

// exp() returns value from exp2(term())
int exp()		// exp: tail-end recursion to call our non-terminals
{
	cout << "exp\n";
	return exp2(term());	// if exp is called, we goto exp2 with our term
}

// term() returns value from term2(fact())
int term()	// term: using tail-end recursion to call non-terminals
{
	cout << "term\n";
	return term2(myNum()); // myNum changed from fact()
}

int fact()
{
	cout << "fact\n";
	if (indexx < prog.length())
	{
		char a = prog.at(indexx++);
		if (a == '(')
		{
			cout << "paren\n";
			while(a != ')') {
				exp();
			};
		}

	}

	return fact2(myNum());
}


// using input 'inp' we make our local variable 'result' be 'inp'
// if the current indexx is less than our prog.length then it is not at the end of string
// we get a single char from program string and make it local variable char 'a'
// if 'a' is '+' we have 'result' value change to exp2(result + term())
// if 'a' is '-' we have 'result' value change to exp2(result - term())
// after all the calls, the 'result' is returned

int exp2(int inp)		// implements right-recursive form to get our 'inp' by
{						// calling exp2 either adding or subtracting our result and our 'term'
	cout << "exp2\n";

	int result = inp;
	if (indexx < prog.length()) //if not the end of program string
	{
		char a = prog.at(indexx++); //get one chr from program string
		if (a == '+')
			result = exp2(result + term()); //handles t+t
		else if (a == '-')
			result = exp2(result - term()); //handles t-t
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
	cout << "term2\n";

	int result = inp;
	if (indexx < prog.length()) //if not the end of program string
	{
		char a = prog.at(indexx++); //get one chr from program string
		if (a == '*')
			result = term2(result * fact()); //handles consecutive * operators
		else if (a == '/')
			result = term2(result / fact()); //handles consecutive / operators
		else if (a == '+' || a == '-') //if + or -, get back one position
			indexx--;
	}
	return result;
}

// fact() has variable char 'a' which is the char character at the current index
// returning the ascii to integer value from char 'a'
// 
int fact2(int inp)
{
	cout << "fact2\n";


	int result = inp;
	if (indexx < prog.length())
	{
		char a = prog.at(indexx++); //get one chr from program string
		if (a == '^')
			{
				cout << "test2\n";
				result = fact2(pow(myNum(), fact()));
			}

	}
	//return atoi(&a); //converts a char to a numeric number and return


	return result;
}
////////int fact2(int inp)
////////{
////////		cout << "fact2\n";
////////	
////////	
////////		int result = inp;
////////		if (indexx < prog.length())
////////		{
////////			char a = prog.at(indexx++); //get one chr from program string
////////			if (a >= '0' && a <= '9')
////////			{
////////				cout << "test1\n";
////////				result = fact2(myNum());
////////			}
////////
////////			else if (a == '^')
////////			{
////////				cout << "test2\n";
////////				result = fact2(pow(myNum(), fact()));
////////			}
////////	
////////		}
////////		//return atoi(&a); //converts a char to a numeric number and return
////////	
////////	
////////		return result;
////////}

int myNum()
{

	cout << "myNum\n";

	char a = prog.at(indexx++); //get one chr from program string
	return atoi(&a); //converts a char to a numeric number and return


	//char a = prog.at(indexx++); //get one chr from program string

	//return atoi(&a); //converts a char to a numeric number and return

}



//////// Interpreter for simplified infix expression with {+, -, *, / } operations;
//////// Keyboard input, single digit numbers only and no spaces are allowed;
//////// compile: $> g++ prog1.cpp
//////// run with: 2+3*4/2+3+4*2
////#include <cstdlib> //for atoi()
////#include <iostream>
////
////#include <string>
////#include <fstream> // file reading
////
////using namespace std;
////
////// Using file input
////
////int Exp(), Term(), Fact(), Exp2(int), Term2(int), Fact2(int);
////
////string prog; //string for reading 1-line input expression (program)
////int indexx = 0; //global index for program string
////
////int main(int argc, const char** argv)
////{
////	string tempString;
////	char tempChar;
////
////	ifstream myFile;
////	myFile.open("myProg.txt");
////
////	while (!myFile.eof()) {		// While it is not the end of file
////
////		myFile.get(tempChar);	// we get the char from file
////		if (tempChar != ' ') {	// if the char is not a space,
////			tempString += tempChar;	// we insert it into the string
////		}
////
////		prog = tempString;			// prog now contains tempString
////
////	}
////	myFile.close();				// We then close the file
////
////
////	//cout << ">";				// Original code
////	//cin >> prog;				// user inserts prog
////
////	cout << "\nresult= " << Exp() << endl;
////
////
////
////}
////
////// Exp() returns value from Exp2(Term())
////int Exp()		// Exp: tail-end recursion to call our non-terminals
////{
////	cout << "Exp\n";
////	return Exp2(Term());	// If Exp is called, we goto Exp2 with our term
////}
////
////// Term() returns value from Term2(Fact())
////int Term()	// Term: Using tail-end recursion to call non-terminals
////{
////	cout << "Term\n";
////	return Term2(Fact());
////}
////
////int Fact() {
////
////	cout << "Fact\n";
////	return Fact2(Fact());
////
////}
////
////
////
////// using input 'inp' we make our local variable 'result' be 'inp'
////// if the current indexx is less than our prog.length then it is not at the end of string
////// we get a single char from program string and make it local variable char 'a'
////// if 'a' is '+' we have 'result' value change to Exp2(result + Term())
////// if 'a' is '-' we have 'result' value change to Exp2(result - Term())
////// after all the calls, the 'result' is returned
////
////int Exp2(int inp)		// Implements right-recursive form to get our 'inp' by
////{						// calling Exp2 either adding or subtracting our result and our 'Term'
////	cout << "Exp2\n";
////
////	int result = inp;
////	if (indexx < prog.length()) //if not the end of program string
////	{
////		char a = prog.at(indexx++); //get one chr from program string
////		if (a == '+')
////			result = Exp2(result + Term()); //handles T+T
////		else if (a == '-')
////			result = Exp2(result - Term()); //handles T-T
////	}
////	return result;
////}
////
////
////// using input 'inp' we make it a local variable 'result' be 'inp'
////// If our 'indexx' is less than the length of 'prog' then it is not the end of string, so we continue
////// we then get char 'a' to be a single char from the string
////// if 'a' is '*' we have 'result' value change to Term2(result * Term())
////// if 'a' is '/' we have 'result' value change to Term2(result / Term())
////// if 'a' is either '+' or '-' then we go back one position
////// After all these we return our result
////
////int Term2(int inp)
////{
////	cout << "Term2\n";
////
////	int result = inp;
////	if (indexx < prog.length()) //if not the end of program string
////	{
////		char a = prog.at(indexx++); //get one chr from program string
////		if (a == '*')
////			result = Term2(result * Fact()); //handles consecutive * operators
////		else if (a == '/')
////			result = Term2(result / Fact()); //handles consecutive / operators
////		else if (a == '+' || a == '-') //if + or -, get back one position
////			indexx--;
////	}
////	return result;
////}
////
////// Fact() has variable char 'a' which is the char character at the current index
////// returning the ascii to integer value from char 'a'
////int Fact2(int inp)
////{
////	cout << "Fact2\n";
////
////
////	int result = inp;
////	if (indexx < prog.length())
////	{
////		char a = prog.at(indexx++); //get one chr from program string
////		if (a >= '0' && a <= '9')
////			result = atoi(&a);
////		else if (a == '^')
////			result = Fact2(pow(result, Fact()));
////
////	}
////	//return atoi(&a); //converts a char to a numeric number and return
////
////
////	return result;
////}
