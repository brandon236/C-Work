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
	{
	cout << "*** copy constructor: size 3 array" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	print_array(a);

	dynamic_array a0(a);
	print_array(a);
	print_array(a0);

	cout << "a.remove(0, 2);" << endl;
	a.remove(0, 2);
	print_array(a);
	print_array(a0);
	}

	{
	cout << "*** operator=: size 3 array" << endl;
	dynamic_array a;
	a.insert(0,0);
	a.insert(2,1);
	a.insert(4,2);
	print_array(a);

	dynamic_array a0;
	a0 = a;
	print_array(a);
	print_array(a0);

	cout << "a.remove(0, 2);" << endl;
	a.remove(0, 2);
	print_array(a);
	print_array(a0);
	}
}
