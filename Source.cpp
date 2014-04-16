#include<iostream>
#include "matrix.h"
#include "matrix.cpp"

using namespace std;

int main ( )
{
	matrix <float> A, B, X;

	float arr[] = { 3.0, 4.0, 5.0, 2.0, 7.0, 5.0, 1.0, 3.0, 4.0 };

	A.assign ( 3, 3, arr );

	float arr2[] = { 6.0, 3.0, 2.0 };

	B.assign( 3, 1, arr2 );

	X = X.cram( A, B);

	for (unsigned int i = 0; i < X.numRows( ); i++)
	{
		cout<<X(i,0)<<endl;
	}

	getchar( );

	return 0;
}
