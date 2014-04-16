#pragma once

#include "matrix.h"

using namespace std;

template <class T>
matrix<T>::matrix(void)
{
}

template <class T>
matrix<T>::matrix(int _rows, int _cols)
{
	for (int i = 0; i < _rows; i++)
	{
		mat.push_back( vector<T>() );

		for (int j = 0; j < _cols; j++)
		{
			mat[i].push_back( 0 );
		}
	}
}

template <class T>
matrix<T>::matrix(vector<T> _mat)
{
	mat.push_back( _mat );
}

template <class T>
matrix<T>::matrix(vector<vector<T> > _mat)
{
	mat = _mat;
}

template <class T>
matrix<T>::~matrix(void)
{
	mat.clear( );
}

template <class T>
T matrix<T> :: operator( ) ( unsigned int _row, unsigned int _col ) const
{
	return mat[_row][_col];
}

template <class T>
T & matrix<T> :: operator( ) ( unsigned int _row, unsigned int _col )
{
	return mat[_row][_col];
}

template <class T>
matrix<T> matrix<T> :: operator( ) ( unsigned int _row )
{
	matrix<T> rowMatrix( mat[_row] );
	
	return rowMatrix;
}

template <class T>
vector<T> matrix<T> :: getRowVector( unsigned int _row )
{
	return mat[_row];
}

template <class T>
vector<T> matrix<T> :: getColVector( unsigned int _col )
{
	vector<T> colVector( mat.size() );

	for (int i = 0; i < mat.size(); i++)
	{
		colVector[i] = mat[i][_col];
	}

	return colVector;
}

template <class T>
matrix<T> matrix<T> :: getRow( unsigned int _row )
{
	return mat(_row);
}

template <class T>
matrix<T> matrix<T> :: getCol( unsigned int _col )
{
	matrix<T> colMatrix( mat.size( ), 1 );

	for (int i = 0; i < mat.size(); i++)
	{
		colMatrix[i][0] = mat[i][_col];
	}

	return colMatrix;
}

template <class T>
unsigned int matrix<T> :: numRows( )
{
	return mat.size( );
}

template <class T>
unsigned int matrix<T> :: numCols( )
{
	return mat[0].size( );
}

template <class T>
matrix<T> matrix<T> :: operator+ ( matrix<T> _mat )
{
	matrix<T> resultantMatrix( numRows( ), numCols( ));

	if( ( numRows( ) != _mat.numRows( ) ) || ( numCols( ) != _mat.numCols( ) ) )
	{
		cerr<<" Addition not possible as matrix dimensions don't match. ";
		return resultantMatrix;
	}

	for (unsigned int i = 0; i < numRows( ); i++)
	{
		for (unsigned int j = 0; j < numCols( ); j++)
		{
			resultantMatrix(i ,j) = mat[i][j] + _mat(i, j);
		}
	}

	return resultantMatrix;
}

template <class T>
matrix<T> matrix<T> :: operator- ( matrix<T> _mat )
{
	matrix<T> resultantMatrix( numRows( ), numCols( ));

	if( ( numRows( ) != _mat.numRows( ) ) || ( numCols( ) != _mat.numCols( ) ) )
	{
		cerr<<" Subtraction not possible as matrix dimensions don't match. ";
		return resultantMatrix;
	}

	for (int i = 0; i < numRows( ); i++)
	{
		for (int j = 0; j < numCols( ); j++)
		{
			resultantMatrix(i ,j) = mat[i][j] - _mat(i, j);
		}
	}

	return resultantMatrix;
}

template <class T>
matrix<T> matrix<T> :: operator* ( matrix<T> _mat )
{
	matrix<T> resultantMatrix( numRows( ), _mat.numCols( ));

	if( ( numCols( ) != _mat.numRows( ) ) )
	{
		cerr<<" Multiplication not defined. ";
		return resultantMatrix;
	}

	for (unsigned int i = 0; i < numRows( ); i++)
	{
		for (unsigned int j = 0; j < _mat.numCols( ); j++)
		{
			resultantMatrix(i, j) = 0;

			for (unsigned int k = 0; k < numCols( ); k++)
			{
				resultantMatrix(i, j) += mat[i][k] * _mat(k, j);
			}
		}
	}

	return resultantMatrix;
}

template <class T>
matrix<T> matrix<T> :: operator= ( matrix<T> _mat )
{
	mat.clear( );
	
	for (unsigned int i = 0; i < _mat.numRows( ); i++)
	{
		mat.push_back( vector<T>() );

		for (unsigned int j = 0; j < _mat.numCols( ); j++)
		{
			mat[i].push_back( _mat(i, j) );
		}
	}

	return *this;
}

template <class T>
matrix<T> matrix<T> :: transpose ( )
{
	matrix<T> transposedMatrix( numCols( ), numRows( ) );

	for (int i = 0; i < numRows( ); i++)
	{
		for (int j = 0; j < numCols( ); j++)
		{
			transposedMatrix(j, i) = mat[i][j];
		}
	}

	return transposedMatrix;
}

template <class T>
matrix<T> matrix<T> :: addRow( )
{
	int newRow = numRows( );

	mat.push_back( vector<T>() );

	for (unsigned int i = 0; i < numCols( ); i++)
	{
		mat[newRow].push_back( 0 );
	}

	return *this;
}


template <class T>
matrix<T> matrix<T> :: addCol( )
{
	for (unsigned int i = 0; i < numRows( ); i++)
	{
		mat[i].push_back( 0 );
	}

	return *this;
}

template <class T>
matrix<T> matrix<T> :: assign ( int _rows, int _cols, T _values[] )
{
	mat.clear( ); 
	unsigned int k = 0;

	for (int i = 0; i < _rows; i++)
	{
		mat.push_back( vector<T>() );

		for (int j = 0; j < _cols; j++)
		{
			mat[i].push_back( _values[k++] );
		}
	}

	return *this;
}

template <class T>
T matrix<T> :: det ( )
{
	if( numRows( ) != numCols( ) )
	{
		cerr<<"Matrix not sqaure";
		return 0;
	}

	matrix<T> subMatrix( numRows( ) - 1, numCols( ) - 1 );
	int size = numRows( );
	T determinant = 0;

	if( size == 2 )
	{
		return (( mat[0][0] * mat[1][1] ) - ( mat[0][1] * mat[1][0] ));
	}
	else
	{
		for( int colCounter = 0 ; colCounter < size ; colCounter ++ )
		{
			int subi = 0;

			for (int i = 1; i < size; i++)
			{
				int subj = 0;

				for (int j = 0; j < size; j++)
				{
					if (colCounter == j)
						continue;

					else
					{
						subMatrix(subi,subj) = mat[i][j];
						subj++;
					}

				}

				subi++;
			}

			determinant += pow(-1, colCounter) * mat[0][colCounter] * subMatrix.det( );
		}

	}

	return determinant;
}

template <class T>
matrix<T> matrix<T> :: replaceRow ( matrix<T> _rowMatrix, int _rowIndex, int _row = 0 )
{
	matrix<T> newMatrix ( mat );

	for (unsigned int i = 0; i < newMatrix.numCols( ); i++)
	{
		newMatrix(_rowIndex, i) = _rowMatrix(_row, i);
	}

	return newMatrix;
}

template <class T>
matrix<T> matrix<T> :: replaceCol ( matrix<T> _colMatrix, int _colIndex, int _col = 0 )
{
	matrix<T> newMatrix ( mat );

	for (unsigned int i = 0; i < newMatrix.numRows( ); i++)
	{
		newMatrix(i, _colIndex) = _colMatrix(i, _col);
	}

	return newMatrix;
}

template <class T>
matrix<T> matrix<T> :: cram ( matrix<T> _coefficientMatrix, matrix<T> _matrixB )
{
	if( _coefficientMatrix.numRows( ) != _matrixB.numRows( ) )
	{
		cerr<<" Number of rows of the matrices don't match";
		return matrix<T> ( _coefficientMatrix.numRows( ), _coefficientMatrix.numCols( ) );
	}

	matrix<T> variableMatrix( _coefficientMatrix.numRows( ), 1 );

	T determinant = _coefficientMatrix.det( );

	for (unsigned int i = 0; i < _coefficientMatrix.numRows( ); i++)
	{
		variableMatrix(i, 0 ) = _coefficientMatrix.replaceCol( _matrixB, i ).det( ) / determinant;
	}

	return variableMatrix;
}