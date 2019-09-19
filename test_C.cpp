#include <iostream>
#include <stdlib.h>

#include "dynamic_array.h"

using namespace std;

void print_array(dynamic_array &a) {
	cout << "size: " << a.get_size() << endl;
	cout << "allocated size: " << a.get_allocated_size() << endl;
	for (int i = 0; i < a.get_size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main() {
	cout << "********** INSERT" << endl;
	cout << "***** no reallocation" << endl;
	{
	cout << "*** in size 3 array, insert size 2 array at 0" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	print_array(a);

	dynamic_array a0;
	a0.insert(1,0);
	a0.insert(3,1);

	a.insert(a0,0);
	print_array(a);
	}
	{
	cout << "*** in size 3 array, insert size 2 array at 1" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	print_array(a);

	dynamic_array a0;
	a0.insert(1,0);
	a0.insert(3,1);

	a.insert(a0,1);
	print_array(a);
	}
	{
	cout << "*** in size 3 array, insert size 2 array at 2" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	print_array(a);

	dynamic_array a0;
	a0.insert(1,0);
	a0.insert(3,1);

	a.insert(a0,2);
	print_array(a);
	}
	{
	cout << "*** in size 3 array, insert size 2 array at 3" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	print_array(a);

	dynamic_array a0;
	a0.insert(1,0);
	a0.insert(3,1);

	a.insert(a0,3);
	print_array(a);

	cout << "*** trigger subscript range exception" << endl;
	try {
		a.insert(a0,6);
	} catch (dynamic_array::exception x) {
		cout << "caught: " << x.n << endl;
	}
	}

	cout << "***** reallocation" << endl;
	{
	cout << "*** in size 3 array, insert size 3 array at 0" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	print_array(a);

	dynamic_array a0;
	a0.insert(1,0);
	a0.insert(3,1);
	a0.insert(5,2);

	a.insert(a0,0);
	print_array(a);
	}
	{
	cout << "*** in size 3 array, insert size 3 array at 1" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	print_array(a);

	dynamic_array a0;
	a0.insert(1,0);
	a0.insert(3,1);
	a0.insert(5,2);

	a.insert(a0,1);
	print_array(a);
	}
	{
	cout << "*** in size 3 array, insert size 3 array at 2" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	print_array(a);

	dynamic_array a0;
	a0.insert(1,0);
	a0.insert(3,1);
	a0.insert(5,2);

	a.insert(a0,2);
	print_array(a);
	}

	cout << "********** REMOVE" << endl;
	cout << "***** no reallocation" << endl;
	{
	cout << "*** in size 4 array, remove [0,1)" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	a.insert(6,3);
	print_array(a);

	a.remove(0,1);
	print_array(a);
	}
	{
	cout << "*** in size 4 array, remove [0,2)" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	a.insert(6,3);
	print_array(a);

	a.remove(0,2);
	print_array(a);
	}
	{
	cout << "*** in size 4 array, remove [1,3)" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	a.insert(6,3);
	print_array(a);

	a.remove(1,3);
	print_array(a);

	cout << "*** trigger subscript range exception" << endl;
	try {
		a.remove(0,3);
	} catch (dynamic_array::exception x) {
		cout << "caught: " << x.n << endl;
	}
	print_array(a);
	}

	cout << "***** reallocation" << endl;
	{
	cout << "*** in size 6 array, remove [0,1)" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	a.insert(6,3);
	a.insert(8,4);
	a.insert(10,5);
	print_array(a);

	a.remove(0,1);
	print_array(a);
	}
	{
	cout << "*** in size 6 array, remove [1,2)" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	a.insert(6,3);
	a.insert(8,4);
	a.insert(10,5);
	print_array(a);

	a.remove(1,2);
	print_array(a);
	}
	{
	cout << "*** in size 6 array, remove [5,6)" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	a.insert(6,3);
	a.insert(8,4);
	a.insert(10,5);
	print_array(a);

	a.remove(5,6);
	print_array(a);
	}

	{
	cout << "*** in size 6 array, remove [1,6)" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	a.insert(6,3);
	a.insert(8,4);
	a.insert(10,5);
	print_array(a);

	a.remove(1,6);
	print_array(a);
	}
	{
	cout << "*** in size 6 array, remove [0,6)" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	a.insert(6,3);
	a.insert(8,4);
	a.insert(10,5);
	print_array(a);

	a.remove(0,6);
	print_array(a);
	}
}
