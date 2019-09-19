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
	cout << "***** create array size: 6" << endl;
	dynamic_array a;
	for (int i = 0; i < 6; i++) {
		a.insert(2*i,i);
	}
	print_array(a);

	cout << "*** remove(0)" << endl;
	a.remove(0);
	print_array(a);

	cout << "*** remove(2)" << endl;
	a.remove(2);
	print_array(a);

	cout << "*** remove(3)" << endl;
	a.remove(3);
	print_array(a);

	cout << "***** trigger subscript range exception" << endl;
	try {
		a.remove(3);
	} catch (dynamic_array::exception x) {
		cout << "caught: " << x.n << endl;
	}
	print_array(a);
}
