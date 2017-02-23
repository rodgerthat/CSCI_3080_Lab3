/*
 * =====================================================================================
 *
 *       Filename:  Lab3.cpp
 *
 *    Description:  Output the tables of truth to determine equivalency for
 *                  two wffs 
 *
 *        Version:  1.0
 *        Created:  02/20/2017 03:21:18 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Norris, Joel R.
 *          Class:  CSCI_3080
 *        Section:  001
 *     Instructor:  Dr. Pettey
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

// variables
const int boolArraySize = 8;  // 
char c;		// holder for incoming characters from cin

// hard coded truth table values for P, Q, and R
bool P[boolArraySize] = {true, true, true, true, false, false, false, false};
bool Q[boolArraySize] = {true, true, false, false, true, true, false, false};
bool R[boolArraySize] = {true, false, true, false, true, false, true, false};

// working arrays
bool A[boolArraySize];
bool B[boolArraySize];
bool C[boolArraySize];

// flag for array loading order
bool isAL = false;	// is array A loaded?

// function prototypes
// trying for some SRP
void loadArray( char c, bool *A );				// load one of the working arrays w/ a hardcoded one
void negateArray( bool *A );					// negate an array! wooo!
void evalPostfix();								// evaluate an incoming postfix expression
void printArrays();								// print out all the working arrays
void operateOnArrays( char logicOperator );		// operate on the two working arrays, A and B, given a certain logical operator
bool isOperator( char c );						// check to see if a char is one of the operators specified, A,I,O,N
bool checkC();									// check to see if C is all true
void evalAB();									// perform logic equivalience operatioin on working arrays A and B

// main program logic
int main() {

    // get first expression from user
    cout << "input the first expression:" << endl;

    // eval first expression, store in working array
	evalPostfix();

	loadArray( 'A', C );	// place the results of the first expression eval in C

    // get second expression from user
    cout << "input the second expression:" << endl;

    // eval second expression, store in working array
	evalPostfix();

	loadArray( 'A', B );	// place the results of the second expression eval in B
	loadArray( 'C', A );	// load the results from the first expression back into A
	evalAB();				// evaluate the two final expressions

    //print out final equivalence table and result
	printArrays();

	// check to see if the two results are the same by checking the C working array
	if ( checkC() ) {
		cout << "The two expressions are equivalent" << endl;
	} else {
		cout << "The two expressions are not equivalent" << endl;
	}

    // goto bed
    return 0;
}

// check to see if the incoming char from cin is one of our operators
bool isOperator( char c ) {
	switch (c) {
		case 'A':
		case 'O':
		case 'I':
		case 'N':
			return true;
		default:
			return false;
	}
} 

// evaluate the postfix expression
void evalPostfix() {

	char c;		// holder for incoming char from cin
	
    while ( ( c = cin.get() ) != 'E' ) {

		// check if the char is an operator
		if ( isOperator(c) ) {

			// if N, then negate the loaded Array
			if ( c == 'N' ) {
				// if A is the loaded array, negate array A, otherwise B is the loaded array, so we negate B
				if ( isAL ) {
					negateArray(A);
				} else {
					negateArray(B);
				}
			// if we're not negating a loaded array, we're going to operate on A and B
			} else {
				operateOnArrays( c );
				isAL = true;
			}
		} else {

			if ( isAL ) {
				loadArray( c, B );
				isAL = false;
			} else {
				loadArray( c, A );
				isAL = true;
			}
		}
	}
}

// accepts a char that indicates the logic operations we want to preform. 
// performs said logical operation between the two working arrays,
// then assigns the result back into A.
void operateOnArrays( char logicOperator ) {

	int i = 0;

	switch( logicOperator ) {

		// AND
		case 'A' :
			for (i=0; i<boolArraySize; i++) {
				A[i] = A[i] && B[i];
			}
			break;

		// OR
		case 'O' :

			for (i=0; i<boolArraySize; i++) {
				A[i] = A[i] || B[i];
			}
			break;


		// IMPLIES
		case 'I' :

			for (i=0; i<boolArraySize; i++) {
				 A[i] = (!A[i]) || B[i];
			}
			break;

	}


}


// loadArray function to handle moving arrays around based on a char input
// this would be MUCH MUCH easier w/ pointers. . . 
void loadArray( char c, bool *Z ) {
	
	switch ( c ) {
		case 'P':
			for ( int i=0; i<boolArraySize; i++ ) Z[i] = P[i];
			break;
		case 'Q':
			for ( int i=0; i<boolArraySize; i++ ) Z[i] = Q[i];
			break;
		case 'R':
			for ( int i=0; i<boolArraySize; i++ ) Z[i] = R[i];
			break;
		case 'A':
			for ( int i=0; i<boolArraySize; i++ ) Z[i] = A[i];
			break;
		case 'B':
			for ( int i=0; i<boolArraySize; i++ ) Z[i] = B[i];
			break;
		case 'C':
			for ( int i=0; i<boolArraySize; i++ ) Z[i] = C[i];
			break;
	}
}

// evaluate the two working arrays, A and B and store the results in array C
void evalAB() {
	for ( int i=0; i<boolArraySize; i++ ) {
		C[i] = A[i] == B[i];
	}
}

// check the C array for all true values, thus determining equivalence
bool checkC() {
	for ( int i=0; i<boolArraySize; i++ ) {
		if ( !C[i] ) return false; 
	}
	return true;
}

// does just that, negates all the values in the array
void negateArray( bool *A ) {

	for ( int i=0; i<boolArraySize; i++ ) A[i] = !A[i];

}

// print out the working arrays in table form, human readable
// as opposed to 1 and 0
void printArrays() {
	
	cout << "first\tsecond\tequivalence" << endl;
	
	for ( int i=0; i<boolArraySize; i++ ) {

		if ( A[i] ) cout << "T\t";
		else cout << "F\t";

		if ( B[i] ) cout << "T\t";
		else cout << "F\t";

		if ( C[i] ) cout << "T\t" << endl;
		else cout << "F\t" << endl;
	}
}
