#include <iostream>
#include <stdlib.h>

#include "dynamic_array.h"

using namespace std;

int test_const_operator(const dynamic_array &a, int i) {
	return a[i];
}

void print_array(dynamic_array &a) {
	cout << "size: " << a.get_size() << endl;
	cout << "allocated size: " << a.get_allocated_size() << endl;
	for (int i = 0; i < a.get_size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main() {
	dynamic_array a;

	cout << "***** array size: 0" << endl;
	print_array(a);

	cout << "check for exception in empty array" << endl;
	try {
		a[0];
	} catch (dynamic_array::exception x) {
		cout << "caught: " << x.n << endl;
	}
	try {
		test_const_operator(a, 0);
	} catch (dynamic_array::exception x) {
		cout << "caught const: " << x.n << endl;
	}

	cout << "***** array size: 1" << endl;
	a.insert(2,0);
	cout << test_const_operator(a, 0) << endl;
	print_array(a);

	cout << "***** array size: 2" << endl;
	a.insert(4,1);
	print_array(a);

	cout << "***** array size: 3" << endl;
	a.insert(3,1);
	print_array(a);

	cout << "***** trigger subscript range exception" << endl;
	try {
		a.insert(5,4);
	} catch (dynamic_array::exception x) {
		cout << "caught: " << x.n << endl;
	}

	cout << "***** trigger re-allocation" << endl;
	a.insert(1,0);
	a.insert(5,4);
	a.insert(99,2);
	print_array(a);
}
