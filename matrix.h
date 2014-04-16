/*
	ID Description: 		Implementation of class matrix
							Written by Pushpreet on 23/03/2014
	
	Version:				- 1.0.0

	Features:				- 
	
	Modification Historty:  --/--/----
								- --:--

	Dependencies:			Depends On: class vector
							Used In: 	Project: markov_chains - Main.cpp

*/

#pragma once

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

template <class T>				// template class to store matrices of different types
class matrix
{
protected:
	vector< vector<T> > mat;						// 2D vector to store the address of the 2D array
public:
	// constructors
	matrix ( void );
	matrix ( int _rows, int _cols );
	matrix ( vector<T> _mat );
	matrix ( vector< vector<T> > _mat );
	
	// destructors
	~matrix(void);

	// access functions
	matrix<T> operator( ) ( unsigned int _row );
	T operator( ) ( unsigned int _row, unsigned int _col ) const;
	T & operator( ) ( unsigned int _row, unsigned int _col );
	
	vector<T> getRowVector ( unsigned int _row );
	vector<T> getColVector ( unsigned int _col );

	matrix<T> getRow ( unsigned int _row );
	matrix<T> getCol ( unsigned int _col );

	// modifiers
	matrix<T> addRow ( );
	matrix<T> addCol ( );
	matrix<T> assign ( int _rows, int _cols, T values[] );

	// capacity
	unsigned int numRows( );
	unsigned int numCols( );

	// matrix arithematic
	matrix<T> operator+ ( matrix<T> _mat );
	matrix<T> operator- ( matrix<T> _mat );
	matrix<T> operator* ( matrix<T> _mat );
	matrix<T> operator= ( matrix<T> _mat );

	// transformations
	matrix<T> transpose ( );
	matrix<T> replaceRow ( matrix<T> _rowMatrix, int _rowIndex, int _row = 0 );
	matrix<T> replaceCol ( matrix<T> _colMatrix, int _colIndex, int _col = 0 );

	// operations
	T det ( );
	matrix<T> cram ( matrix<T> _coefficientMatrix, matrix<T> _matrixB );
};

/*
	Changelog:
	
	03/04/2014
		- 01:26 changed storage of matrix from 2D array to 2D vector
	
*/